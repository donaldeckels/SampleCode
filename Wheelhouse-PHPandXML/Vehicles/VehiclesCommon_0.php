<?php
/**
 * Vehicles Management
 * @Team Wheelhouse, CSUN Comp 380
 * @Developed 2014
 * @version 1.4.2

 * Based upon the open source
 
 * Projects Tracker
 *
 * @author Janusz Tylek <jtylek@telaxus.com>, Adam Bukowski <abukowski@telaxus.com>
 * @copyright Copyright &copy; 2008, Telaxus LLC
 * @license MIT
 * @version 1.4.1
 * @package epesi-premium
 * @subpackage projects
 */
defined("_VALID_ACCESS") || die('Direct access forbidden');

class VehiclesCommon extends ModuleCommon {
    public static function get_vehicle($id) {
		static $cache;
		if(!isset($cache[$id]))
			$cache[$id] = Utils_RecordBrowserCommon::get_record('vehicles', $id);
		return $cache[$id];
    }

	public static function get_vehicles($crits=array(),$cols=array(), $order = array(), $limit = array(), $admin = false) {
    		return Utils_RecordBrowserCommon::get_records('vehicles', $crits, $cols, $order, $limit, $admin);
	}

    public static function display_vin($v, $nolink=false) {
		return Utils_RecordBrowserCommon::create_linked_label_r('vehicles', 'VIN', $v, $nolink);
	}
	public static function display_plate($v, $nolink=false) {
		return Utils_RecordBrowserCommon::create_linked_label_r('vehicles', 'License Plate', $v, $nolink);
	}

	public static function menu() {
		if (Utils_RecordBrowserCommon::get_access('vehicles','browse'))
			return array(_M('WheelHouse')=>array('__submenu__'=>2,_M('Vehicles')=>array()));
		else
			return array();
	}

    public static function vehicles_datatype($field = array()) {
        if (!isset($field['QFfield_callback'])) $field['QFfield_callback'] = array('VehiclesCommon', 'QFfield_vehicles');
        if (!isset($field['display_callback'])) $field['display_callback'] = array('VehiclesCommon', 'display__vehicle');
        $field['type'] = $field['param']['field_type'];
        $param = '';
        if ($field['type']=='select') {
            $field['type'] = 'text';
            $param = 64;
        }
        $field['param'] = $param;
        return $field;
    }
	
    public static function display_vehicles($record, $nolink, $desc) {
        $v = $record[$desc['id']];
		if (!is_array($v) && isset($v[1]) && $v[1]!=':') return $v;
        $def = '';
        if (!is_array($v)) $v = array($v);
		if (count($v)>100) return count($v).' '.__('values');
        foreach($v as $k=>$w){
            if ($def) $def .= '<br>';
            $def .= Utils_RecordBrowserCommon::no_wrap(self::autoselect_vehicles_format($w, $nolink));
        }
        if (!$def)  $def = '---';
        return $def;
    }
	
	    public static function display_vehicle($record, $nolink=false, $desc=array()) {
        $v = $record[$desc['id']];
        $def = '';
        $first = true;
        $param = @explode(';',$desc['param']);
        if (!isset($param[1]) || $param[1] == '::') $callback = array('VehiclesCommon', 'vehicles_format_default');
        else $callback = explode('::', $param[1]);
        if (!is_array($v)) $v = array($v);
        foreach($v as $k=>$w){
            if ($w=='') break;
            if ($first) $first = false;
            else $def .= '<br>';
            $def .= Utils_RecordBrowserCommon::no_wrap(call_user_func($callback, self::get_vehicles($w), $nolink));
        }
        if (!$def)  $def = '---';
        return $def;
    }
	
	
	public static function auto_vehicles_suggestbox($str, $fcallback) {
        $words = explode(' ', trim($str));
        $final_nr_of_records = 10;
        $recordset_records = array();
        foreach (array('vehicles'=>'V') as $recordset=>$recordset_indicator) {
			$crits = array();
			foreach ($words as $word) if ($word) {
				$word = DB::Concat(DB::qstr('%'),DB::qstr($word),DB::qstr('%'));
				$crits = Utils_RecordBrowserCommon::merge_crits($crits, array('~"license_plate'=>$word));
				$order = array('license_plate'=>'ASC');
			}
            $recordset_records[$recordset_indicator] = self::get_vehicles($crits, array(), $order, $final_nr_of_records);
		}
        $total = 0;
        foreach ($recordset_records as $records)
            $total += count($records);
        if ($total != 0)
            foreach ($recordset_records as $key => $records)
                $recordset_records[$key] = array_slice($records, 0, ceil($final_nr_of_records * count($records) / $total));
        $ret = array();
        foreach ($recordset_records as $recordset_indicator => $records) {
            foreach ($records as $rec) {
                $key = $recordset_indicator . ':' . $rec['id'];
                $ret[$key] = call_user_func($fcallback, $key, true);
            }
        }
        asort($ret);
        return $ret;
    }
	
	public static function autoselect_vehicles_format($arg, $nolink=false) {
        $icon = array('V' => Base_ThemeCommon::get_template_file('Vehicles', 'icon.png'));
		$x = explode(':', $arg);
        if(count($x)==2) {
            list($rset, $id) = $x;
        } else {
            $id = $x[0];
			$rset = 'V';
        }
        if (!$id) return '---';
		$val = self::vehicles_format_default($id, $nolink);
		$rlabel = __('V');
        $indicator_text = __('Vehicle');
        $rindicator = isset($icon[$rset]) ?
                '<span style="margin:1px 0.5em 1px 1px; width:1.5em; height:1.5em; display:inline-block; vertical-align:middle; background-image:url(\''.$icon[$rset].'\'); background-repeat:no-repeat; background-position:left center; background-size:100%"><span style="display:none">['.$indicator_text.'] </span></span>' : "[$indicator_text] ";
        $val = $rindicator.$val;
        if ($nolink)
            return strip_tags($val);
        return $val;
    }
	
    public static function QFfield_vehicles(&$form, $field, $label, $mode, $default, $desc, $rb_obj = null) {
		$veh = array();
        if ($mode=='add' || $mode=='edit') {
            $fcallback = array('VehiclesCommon','autoselect_vehicles_format');
			$label = Utils_RecordBrowserCommon::get_field_tooltip($label, $desc['type'], array('vehicles'));
            if ($desc['type']=='multiselect') {
                $form->addElement('automulti', $field, $label, array('VehiclesCommon','auto_vehicles_suggestbox'), array($fcallback), $fcallback);
            }  else {
				$form->addElement('autoselect', $field, $label, $cont, array(array('VehiclesCommon','auto_vehicles_suggestbox'), array($fcallback)), $fcallback, array('id'=>$field));
			}
            $form->setDefaults(array($field=>$default));
        } else {
            $callback = $rb_obj->get_display_method($desc['name']);
            if (!is_callable($callback)) $callback = array('VehiclesCommon','display_vehicles');
            $def = call_user_func($callback, $rb_obj->record, false, $desc);
//          $def = call_user_func($callback, array($field=>$default), false, $desc);
            $form->addElement('static', $field, $label, $def);
        }
		
		/*$veh = array();
        $param = explode(';',$desc['param']);
        if ($mode=='add' || $mode=='edit') {
            $adv_crits = null;
            if (!isset($param[1]) || $param[1] == '::') $callback = array('VehiclesCommon', 'vehicles_format_default');
            else $callback = explode('::', $param[1]);
            if (isset($param[2]) && $param[2] != '::') {
                $crit_callback = explode('::',$param[2]);
                if ($crit_callback[0]=='ChainedSelect') {
                    $crits = null;
                } elseif (is_callable($crit_callback)) {
                    $crits = call_user_func($crit_callback, false);
                    $adv_crits = call_user_func($crit_callback, true);
                    if ($adv_crits === $crits) $adv_crits = null;
                } else {
					$crits = array();
					$adv_crits = null;
				}
            } else $crits = array();
            if ($crits===true) $crits = $adv_crits;
            if ($desc['type']!='multiselect' && (!isset($crit_callback) || $crit_callback[0]!='ChainedSelect')) $veh[''] = '---';
            $limit = false;
            if ($crits!==null) {
                $amount = Utils_RecordBrowserCommon::get_records_count('vehicles', $crits);
                $base_crits = $crits;
                if ($amount>Utils_RecordBrowserCommon::$options_limit) {
                    $limit = Utils_RecordBrowserCommon::$options_limit;
                    if ($desc['type']=='select') {
                        $present = false;
                        foreach ($crits as $k=>$v)
                            if (strstr($k, ':Recent')) {
                                $present = true;
                                break;
                            }
                        if (!$present) $base_crits = Utils_RecordBrowserCommon::merge_crits($base_crits, array(':Recent'=>true));
                    }
                }

                $vehicles = self::get_vehicles($base_crits, array(), array(), $limit);
                if (!is_array($default)) {
                    if ($default!='') $default = array($default); else $default=array();
                }
                $ext_rec = array_flip($default);
                foreach ($vehicles as $v) {
                    $veh[$v['id']] = call_user_func($callback, $v, true);
                    unset($ext_rec[$v['id']]);
                }
                foreach($ext_rec as $k=>$v) {
                    $c = self::get_vehicle($k);
                    if ($c===null) continue;
                    $veh[$k] = call_user_func($callback, $c, true);
                }
                uasort($veh, array('VehiclesCommon', 'compare_names'));
            }
			$label = Utils_RecordBrowserCommon::get_field_tooltip($label, $desc['type'], 'vehicles', $crits);
            if ($desc['type']=='select') {
                if (is_numeric($limit)) {
                    unset($veh['']);
                    $form->addElement('autoselect', $field, $label, $veh, array(array('VehiclesCommon','autoselect_vehicles_suggestbox'), array($crits, $callback)), $callback, array('id'=>$field));
                } else
                    $form->addElement($desc['type'], $field, $label, $veh, array('id'=>$field));
            } else {
                if ($adv_crits !== null || is_numeric($limit)) {
                    $form->addElement('automulti', $field, $label, array('VehiclesCommon','autoselect_vehicles_suggestbox'), array($adv_crits!==null?$adv_crits:$crits, $callback), $callback);
                } else {
                    $form->addElement($desc['type'], $field, $label, $veh, array('id'=>$field));
                }
            }
            $form->setDefaults(array($field=>$default));
            if (isset($param[2]) && $param[2] != '::')
                if ($crit_callback[0]=='ChainedSelect') {
                    if ($form->exportValue($field)) $default = $form->exportValue($field);
                    self::vehicles_chainedselect_crits($default, $desc, $callback, $crit_callback[1]);
                }
        } else {
            $callback = $rb_obj->get_display_method($desc['name']);
            if (!is_callable($callback)) $callback = array('VehiclesCommon','display_vehicles');
            $def = call_user_func($callback, $rb_obj->record, false, $desc);
//          $def = call_user_func($callback, array($field=>$default), false, $desc);
            $form->addElement('static', $field, $label, $def);
        }
/*		if ($mode == 'add' || $mode == 'edit'){
			$form->addElement('text',$field, $label, $opts, array('id'=>$field));
			if ($mode =='edit')
				$form->setDefaults(array($field=>$default));
			//$form->addFormRule(array('VehiclesCommon', 'check_vehicles_unique'));
		}
		else {
			$param = explode(';',$desc['param']);
			$callback = $rb_obj->get_display_method($desc['name']);
			if (!is_callable($callback)) $callback = array('VehiclesCommon','display_vehicles');
			$def = call_user_func($callback, $rb_obj->record, false, $desc);
	//      $def = call_user_func($callback, array($field=>$default), false, $desc);
			$form->addElement('static', $field, $label, $def);
		}
*/  }

	public static function automulti_vehicles_suggestbox($str, $crits=array()) {
		$str = explode(' ', trim($str));
        foreach ($str as $k=>$v)
            if ($v) {
                $v = DB::Concat(DB::qstr('%'),DB::qstr($v),DB::qstr('%'));
				$crits = Utils_RecordBrowserCommon::merge_crits($crits, array('(~"license_plate'=>$v,'|~"vin'=>$v));
            }
        $recs = self::get_vehicles($crits, array(), array('license_plate'=>'ASC', 'vin'=>'ASC'), 10);
        $ret = array();
        foreach($recs as $v)
            $ret[$v['id']] = self::vehicles_format_default($v, true);
        return $ret;
    }
	
	public static function autoselect_vehicles_suggestbox($str, $crits, $format_callback) {
        $str = explode(' ', trim($str));
        foreach ($str as $k=>$v)
            if ($v) {
                $v = DB::Concat(DB::qstr('%'),DB::qstr($v),DB::qstr('%'));
                $crits = Utils_RecordBrowserCommon::merge_crits($crits, array('(~"license_plate'=>$v, '|~"vin'=>$v));
            }
        $recs = self::get_vehicles($crits, array(), array('license_plate'=>'ASC','vin'=>'ASC'), 10);
        $ret = array();
        foreach($recs as $v) {
            $ret[$v['id']] = call_user_func($format_callback, $v, true);
        }
        return $ret;
    }
	
	public static function vehicles_chainedselect_crits($default, $desc, $format_func, $ref_field){
        Utils_ChainedSelectCommon::create($desc['id'],array($ref_field),'modules/Vehicles/update_vehicle.php', array('format'=>implode('::', $format_func), 'required'=>$desc['required']), $default);
        return null;
    }
	
	public static function vehicles_format_default($record, $nolink){
        if (is_numeric($record)) $record = self::get_vehicle($record);
        if (!$record) return null;
        $ret = '';
		$format = Base_User_SettingsCommon::get('Vehicles','vehicles_format');
		$label = str_replace(array('##l##','##v##'), array($record['license_plate'], $record['vin']), $format);
        if (!$nolink) {
            $ret .= Utils_RecordBrowserCommon::record_link_open_tag('vehicles', $record['id']);
            $ret .= Utils_TooltipCommon::ajax_create($label,array('VehiclesCommon','vehicles_get_tooltip'), array($record));
            $ret .= Utils_RecordBrowserCommon::record_link_close_tag();
        } else {
            $ret .= $label;
        }
		
        return $ret;
    }
	
	public static function compare_names($a, $b) {
        return strcasecmp(strip_tags($a),strip_tags($b));
    }
	
	public static function vehicles_get_tooltip($record) {
        return Utils_TooltipCommon::format_info_tooltip(array(
                __('Vehicle')=>'<STRONG>'.$record['license_plate'].'</STRONG>',
				__('VIN')=>$record['vin'],
                ));
    }
/*	
	public static function QFfield_unique_vehicle(&$form, $field, $label, $mode, $default, $desc, $rb_obj) {
		$ret = self::QFfield_vehicles($form, $field, $label, $mode, $default, $desc, $rb_obj);
        if ($mode=='add' || $mode=='edit')
			self::add_rule_vehicle_unique($form, $field, $rb_obj->tab, isset($rb_obj->record['id'])?$rb_obj->record['id']:null);
		return $ret;
	}
	
	static $field = null;
	static $rset = null;
	static $rid = null;
	
	public static function add_rule_vehicle_unique($form, $field, $rset=null, $rid=null) {
		self::$field = $field;
		self::$rset = $rset;
		self::$rid = $rid;
		$form->addFormRule(array('VehiclesCommon', 'check_vehicles_unique'));
	}
	
	public static function check_vehicles_unique($data){
		if (!isset($data[self::$field])) return true;
		$veh = $data[self::$field];
		if (!$veh) return true;
		$rec = self::get_record_by_vin($veh, self::$rset, self::$rid);
		if ($rec == false) return true;
		return array(self::$field=>__( 'VIN duplicate found!'));
	}
	
	public static function get_record_by_vin($veh, $rset=null, $rid=null) {
		if ($rid==null) $rset=null;
		$veh = DB::GetRow('SELECT id FROM vehicles WHERE active=1 AND vin '.DB::like().' %s AND id!=%d', array($veh, $rset=='vehicles'?$rid:-1));
		if ($veh)
			return array('vehicles', $veh['id']);
		return false;
	}
	*/
// Filter criteria for Company Name
	public static function vehicles_company_crits(){
//  	   return array(':Fav'=>1);
// gc= GC (General Contractor), res=Residential
		return array('group'=>array('customer'));
   }

// Filter criteria for Epmloyees
// Used in Vehicle Manager
	public static function vehicles_employees_crits(){
		return array('(company_name'=>CRM_ContactsCommon::get_main_company(),'|related_companies'=>array(CRM_ContactsCommon::get_main_company()));
   }


	public static function applet_caption() {
		if (Utils_RecordBrowserCommon::get_access('vehicles','browse'))
			return __('Vehicles');
	}
	public static function applet_info() {
		return __('Vehicles List');
	}

	public static function user_settings() {
		$opts = array(
			'##v## ##l##' => '['.__('VIN').'] ['.__('License Plate').']',
			'##l## ##v##' => '['.__('License Plate').'] ['.__('VIN').']',
			'##l##, ##f##' => '['.__('License Plate').'] ['.__('VIN').']',
			'##v## ##l##' => '['.__('VIN').'] ['.__('License Plate').']'
		);
		return array(__('Regional Settings')=>array(
				array('name'=>'vehicles_header', 'label'=>__('Vehicle display'), 'type'=>'header'),
				array('name'=>'vehicles_format','label'=>__('Vehicle format'),'type'=>'select','values'=>$opts,'default'=>'##l## ##v##')
					),
					__('Filters')=>array( // Until there's an option to define user_settings variables and redirect the display to custom method at the same time, it's the only solution to have this part here
				array('name'=>'show_all_vehicles_in_filters','label'=>__('Show All vehicles in Filters'),'type'=>'hidden','default'=>1)
					));
	}	
	
	
	public static function applet_info_format($r){
		$arr = array(
			__('VIN')=>$r['vin'],
			__('Description')=>htmlspecialchars($r['description'])
		);
		$ret = array('notes'=>Utils_TooltipCommon::format_info_tooltip($arr));
		return $ret;
	}


	public static function applet_settings() {
		return Utils_RecordBrowserCommon::applet_settings(array(
			array('name'=>'my','label'=>__('Display only my vehicles'),'default'=>0,'type'=>'select','values'=>array(0=>__('No'),1=>__('Yes'))),
			));
	}
	
	public static function watchdog_label($rid = null, $events = array(), $details = true) {
		return Utils_RecordBrowserCommon::watchdog_label(
				'vehicles',
				__('Vehicles'),
				$rid,
				$events,
				'vehicles_name',
				$details
			);
	}
	
	public static function search_format($id) {
		if(!Utils_RecordBrowserCommon::get_access('vehicles','browse')) return false;
		$row = self::get_vehicles(array('id'=>$id));
		if(!$row) return false;
		$row = array_pop($row);
		return Utils_RecordBrowserCommon::record_link_open_tag('vehicles', $row['id']).__( 'Vehicle (attachment) #%d, %s %s', array($row['id'], $row['license_plate'], $row['vin'])).Utils_RecordBrowserCommon::record_link_close_tag();
	}


	
	///////////////////////////////////
	// mobile devices

	public static function mobile_menu() {
		if(!Acl::is_user())
			return array();
		return array(__('Vehicles')=>'mobile_vehicles');
	}
	
	public static function mobile_vehicles() {
		$me = CRM_ContactsCommon::get_my_record();
		$defaults = array('vehicles_manager'=>$me['id'], 'start_date'=>date('Y-m-d'));
		Utils_RecordBrowserCommon::mobile_rb('vehicles',array('vehicles_manager'=>$me['id']), array('vin'=>'ASC'),array('customer'=>1),$defaults);
	}
}
?>
