<?php

/**
 * Description of PartsCommon_0
 * WheelHouse Parts Module
 * @author Team WheelHouse
  * @version 1.5.2
 */
defined("_VALID_ACCESS") || die('Direct access forbidden');

class PartsCommon extends ModuleCommon 
{
	
	public static function help() 
        {
		return Base_HelpCommon::retrieve_help_from_file(self::Instance()->get_type());
	}
        
        
        public static function get_part($id) {
		return Utils_RecordBrowserCommon::get_record('parts', $id);
    }

	public static function get_parts($crits=array(),$cols=array()) {
    		return Utils_RecordBrowserCommon::get_records('parts', $crits, $cols);
	}

        public static function display_part_name($v, $nolink=false) {
		return Utils_RecordBrowserCommon::create_linked_label_r('parts', 'Part Name', $v, $nolink);
	}
        
        public static function display_brand($v, $nolink=false) {
		return Utils_RecordBrowserCommon::create_linked_label_r('parts', 'Manufacturer', $v, $nolink);
	}
        
        public static function display_partNum($v, $nolink=false) {
		return Utils_RecordBrowserCommon::create_linked_label_r('parts', 'Part Number', $v, $nolink);
	}
       
        public static function display_price($v, $nolink=false) {
		return Utils_RecordBrowserCommon::create_linked_label_r('parts', 'Price', $v, $nolink);
	}
        
	public static function menu() {
		if (Utils_RecordBrowserCommon::get_access('parts','browse'))
			return array(_M('WheelHouse')=>array('__submenu__'=>3,_M('Parts')=>array()));
		else
			return array();
	}

// Filter criteria for Company Name
	public static function parts_company_crits(){
//  	   return array(':Fav'=>1);
// gc= GC (General Contractor), res=Residential
		return array('group'=>array('Vendor'));
   }

// Filter criteria for Epmloyees
// Used in Service Order Manager
	public static function parts_vendor_crits(){
		return array('(company_name'=>CRM_ContactsCommon::get_main_company(),'|related_companies'=>array(CRM_ContactsCommon::get_main_company()));
   }

   public function display_SKU($record)
           {
		if($record['id'] == 0){
			return 'Created After Part is Saved';
		}
		else{
			return  'SKU000'.$record['id'];
		}
	}

	public static function applet_caption() {
		if (Utils_RecordBrowserCommon::get_access('parts','browse'))
			return __('Parts');
	}
	public static function applet_info() {
		return __('Part List');
	}

	public static function applet_info_format($r){
		$arr = array(
			__('Part Name')=>$r['parts_name'], //*************************
			__('Description')=>htmlspecialchars($r['description'])
		);
		$ret = array('notes'=>Utils_TooltipCommon::format_info_tooltip($arr));
		return $ret;
	}


	public static function applet_settings() {
		return Utils_RecordBrowserCommon::applet_settings(array(
			array('name'=>'status','label'=>__('Display parts with status'),'default'=>3,'type'=>'select','values'=>array('__NULL__'=>'['.__('All active').']','__ALL__'=>'['.__('All').']')+$sts),
			array('name'=>'my','label'=>__('Display only my parts'),'default'=>1,'type'=>'select','values'=>array(0=>__('No'),1=>__('Yes'))),
			));
	}
	
	public static function watchdog_label($rid = null, $events = array(), $details = true) {
		return Utils_RecordBrowserCommon::watchdog_label(
				'parts',
				__('Parts'),
				$rid,
				$events,
				'part_name',
				$details
			);
	}
	
	public static function search_format($id) {
		if(!Utils_RecordBrowserCommon::get_access('parts','browse')) return false;
		$row = self::get_parts(array('id'=>$id));
		if(!$row) return false;
		$row = array_pop($row);
		return Utils_RecordBrowserCommon::record_link_open_tag('parts', $row['id']).__( 'Part (attachment) #%d, %s', array($row['id'], $row['part_name'])).Utils_RecordBrowserCommon::record_link_close_tag();
	}

	public static function parts_datatype($field = array()) {
        if (!isset($field['QFfield_callback'])) $field['QFfield_callback'] = array('PartsCommon', 'QFfield_part');
        if (!isset($field['display_callback'])) $field['display_callback'] = array('PartsCommon', 'display_part');
        $field['type'] = $field['param']['field_type'];
        $param = 'parts::Part Number|Part Name';
        if (isset($field['param']['format'])) $param .= ';'.implode('::',$field['param']['format']);
        else $param .= ';::';
        if (isset($field['param']['crits'])) $param .= ';'.implode('::',$field['param']['crits']);
        else $param .= ';::';
        $field['param'] = $param;
        return $field;
    }
	
	public static function QFfield_part(&$form, $field, $label, $mode, $default, $desc, $rb_obj = null) {
        $cont = array();
        $param = explode(';',$desc['param']);
        if ($mode=='add' || $mode=='edit') {
            $adv_crits = null;
            if (!isset($param[1]) || $param[1] == '::') $callback = array('PartsCommon', 'part_format_default');
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
            if ($desc['type']!='multiselect' && (!isset($crit_callback) || $crit_callback[0]!='ChainedSelect')) $cont[''] = '---';
            $limit = false;
            if ($crits!==null) {
                $amount = Utils_RecordBrowserCommon::get_records_count('parts', $crits);
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

                $parts = self::get_parts($base_crits, array(), array(), $limit);
                if (!is_array($default)) {
                    if ($default!='') $default = array($default); else $default=array();
                }
                $ext_rec = array_flip($default);
                foreach ($parts as $v) {
                    $cont[$v['id']] = call_user_func($callback, $v, true);
                    unset($ext_rec[$v['id']]);
                }
                foreach($ext_rec as $k=>$v) {
                    $c = PartsCommon::get_part($k);
                    if ($c===null) continue;
                    $cont[$k] = call_user_func($callback, $c, true);
                }
                
            }
			$label = Utils_RecordBrowserCommon::get_field_tooltip($label, $desc['type'], 'parts', $crits);
            if ($desc['type']=='select') {
                if (is_numeric($limit)) {
                    unset($cont['']);
                    $form->addElement('autoselect', $field, $label, $cont, array(array('PartsCommon','autoselect_parts_suggestbox'), array($crits, $callback)), $callback, array('id'=>$field));
                } else
                    $form->addElement($desc['type'], $field, $label, $cont, array('id'=>$field));
            } else {
                if ($adv_crits !== null || is_numeric($limit)) {
                    $form->addElement('automulti', $field, $label, array('PartsCommon','autoselect_parts_suggestbox'), array($adv_crits!==null?$adv_crits:$crits, $callback), $callback);
                } else {
                    $form->addElement($desc['type'], $field, $label, $cont, array('id'=>$field));
                }
            }
            $form->setDefaults(array($field=>$default));
            if (isset($param[2]) && $param[2] != '::')
                if ($crit_callback[0]=='ChainedSelect') {
                    if ($form->exportValue($field)) $default = $form->exportValue($field);
                    self::parts_chainedselect_crits($default, $desc, $callback, $crit_callback[1]);
                }
        } else {
            $callback = $rb_obj->get_display_method($desc['name']);
            if (!is_callable($callback)) $callback = array('PartsCommon','display_part');
            $def = call_user_func($callback, $rb_obj->record, false, $desc);
//          $def = call_user_func($callback, array($field=>$default), false, $desc);
            $form->addElement('static', $field, $label, $def);
        }
    }
	
	
	
    public static function display_part($record, $nolink=false, $desc=null) {
        if ($desc!==null) $v = $record[$desc['id']];
        elseif(is_array($record)) $v = $record['id'];
        else $v = $record;
        if (!is_numeric($v) && !is_array($v)) return $v;
		if ($v==-1) return '---';
        $def = '';
        $first = true;
        if (!is_array($v)) $v = array($v);
        foreach($v as $k=>$w){
            if ($w=='') break;
            if ($first) $first = false;
            else $def .= '<br>';
            $def .= Utils_RecordBrowserCommon::no_wrap(Utils_RecordBrowserCommon::create_linked_label('parts', 'Part Name', $w, $nolink));
        }
        if (!$def) return '---';
        return $def;
    }
	
	public static function part_format_default($record, $nolink=false){
        if (is_numeric($record)) $record = self::get_part($record);
        if (!$record) return null;
        $ret = '';
        if (!$nolink) {
            $ret .= Utils_RecordBrowserCommon::record_link_open_tag('parts', $record['id']);
            $ret .= Utils_TooltipCommon::ajax_create($label,array('PartsCommon','part_get_tooltip'), array($record));
            $ret .= Utils_RecordBrowserCommon::record_link_close_tag();
        } else {
            $ret .= $record['part_name'];
        }
        return $ret;
    }
	
	public static function autoselect_parts_suggestbox($str, $crits, $format_callback, $inc_vendors = false) {
        $str = explode(' ', trim($str));
        foreach ($str as $k=>$v)
            if ($v) {
                $v = DB::Concat(DB::qstr('%'),DB::qstr($v),DB::qstr('%'));
                $crits = Utils_RecordBrowserCommon::merge_crits($crits, array('(~"last_name'=>$v,'|~"part_name'=>$v));
            }
        $recs = Utils_RecordBrowserCommon::get_records('parts', $crits, array(), array('part_name'=>'ASC'), 10);
        $ret = array();
        foreach($recs as $v) {
            $ret[$v['id']] = call_user_func($format_callback, $v, true);
        }
        return $ret;
    }
	
	public static function user_settings() {
		$opts = array(
			'##n## ##u###' => '['.__('Part Number').'] ['.__('Part Name').']'
		);
		return array(__('Regional Settings')=>array(
				array('name'=>'contact_header', 'label'=>__('Parts display'), 'type'=>'header'),
				array('name'=>'contact_format','label'=>__('Parts format'),'type'=>'select','values'=>$opts,'default'=>'##n## ##u##')
					),
					__('Filters')=>array( // Until there's an option to define user_settings variables and redirect the display to custom method at the same time, it's the only solution to have this part here
				array('name'=>'show_all_parts_in_filters','label'=>__('Show All Parts in Filters'),'type'=>'hidden','default'=>1)
					));
	}
	
	public static function part_get_tooltip($record) {
		if (!$record[':active']) return '';
		if (!Utils_RecordBrowserCommon::get_access('parts', 'view', $record)) return '';
        if(!is_array($record) || empty($record)) return '';
        return Utils_TooltipCommon::format_info_tooltip(array(
                __('SKU ID')=>'<STRONG>'.$record['SKU ID'].'</STRONG>',
                __('Part Name') =>$record['part_name'],
                __('Part Number')=>$record['part_number'],
                __('Vendor')=>$record['vendor'],
				__('Price')=>'$'.$record['price'],
                ));
    }

	
	///////////////////////////////////
	// mobile devices

	public static function mobile_menu() {
		if(!Acl::is_user())
			return array();
		return array(__('Parts')=>'mobile_parts');
	}
	
	public static function mobile_parts() {
		$me = CRM_ContactsCommon::get_my_record();
		$defaults = array('parts_manager'=>$me['id'],);
		Utils_RecordBrowserCommon::mobile_rb('parts',array('parts_manager'=>$me['id'], '!status'=>array(2,4)),array('parts_name'=>'ASC'),array('customer'=>1),$defaults);
	}
        
    
}
