<?php
/**
 * Service Orders Management
 * @Team Wheelhouse, CSUN Comp 380
 * @Developed 2014
 * @version 3.3.3

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



class ServiceOrdersCommon extends ModuleCommon {

	private static $ID = 1;

    public static function get_serviceorder($id) {
		return Utils_RecordBrowserCommon::get_record('serviceorders', $id);
    }

	public static function get_serviceorders($crits=array(),$cols=array()) {
    		return Utils_RecordBrowserCommon::get_records('serviceorders', $crits, $cols);
	}

    public static function display_so_name($v, $nolink=false) {
		return Utils_RecordBrowserCommon::create_linked_label_r('serviceorders', 'ServiceOrder Name', $v, $nolink);
	}

	public static function menu() {
		if (Utils_RecordBrowserCommon::get_access('serviceorders','browse'))
			//return array(_M('ServiceOrders')=>array());
			return array(_M('WheelHouse')=>array('__submenu__'=>1,_M('ServiceOrders')=>array()));
		else
			return array();
	}
// Filter criteria for Company Name
	public static function serviceorders_company_crits(){
//  	   return array(':Fav'=>1);
// gc= GC (General Contractor), res=Residential
		return array('group'=>array('customer'));
   }

// Filter criteria for Epmloyees
// Used in Service Order Manager
	public static function serviceorders_employees_crits(){
		return array('(company_name'=>CRM_ContactsCommon::get_main_company());
   }
   
   
	public static function applet_caption() {
		if (Utils_RecordBrowserCommon::get_access('serviceorders','browse'))
			return __('ServiceOrders');
	}
	public static function applet_info() {
		return __('ServiceOrders List');
	}

	public static function applet_info_format($r){
		$arr = array(
			__('ServiceOrder Name')=>$r['serviceorder_name'],
			__('Due Date')=>Base_RegionalSettingsCommon::time2reg($r['due_date'], false),
			__('Description')=>htmlspecialchars($r['description'])
		);
		$ret = array('notes'=>Utils_TooltipCommon::format_info_tooltip($arr));
		return $ret;
	}


	public static function applet_settings() {
		$sts = Utils_CommonDataCommon::get_array('ServiceOrders_Status');
		return Utils_RecordBrowserCommon::applet_settings(array(
			array('name'=>'status','label'=>__('Display serviceorders with status'),'default'=>'__ALL__','type'=>'select','values'=>array('__NULL__'=>'['.__('All active').']','__ALL__'=>'['.__('All').']')+$sts),
			array('name'=>'my','label'=>__('Display only my serviceorders'),'default'=>0,'type'=>'select','values'=>array(0=>__('No'),1=>__('Yes'))),
			));
	}
	
	public static function watchdog_label($rid = null, $events = array(), $details = true) {
		return Utils_RecordBrowserCommon::watchdog_label(
				'serviceorders',
				__('ServiceOrders'),
				$rid,
				$events,
				'serviceorder_name',
				$details
			);
	}
	
	public static function search_format($id) {
		if(!Utils_RecordBrowserCommon::get_access('serviceorders','browse')) return false;
		$row = self::get_serviceorders(array('id'=>$id));
		if(!$row) return false;
		$row = array_pop($row);
		return Utils_RecordBrowserCommon::record_link_open_tag('serviceorders', $row['id']).__( 'ServiceOrder (attachment) #%d, %s', array($row['id'], $row['serviceorder_name'])).Utils_RecordBrowserCommon::record_link_close_tag();
	}
	
	public function display_serviceorder_id($record){
		if($record['id'] == 0){
			return 'Created After Saved';
		}
		else{
			return 'SO#'.str_pad($record['id'], 6, '0', STR_PAD_LEFT);
		}
	}



	
	///////////////////////////////////
	// mobile devices

	public static function mobile_menu() {
		if(!Acl::is_user())
			return array();
		return array(__('ServiceOrders')=>'mobile_serviceorders');
	}
	
	public static function mobile_serviceorders() {
		$me = CRM_ContactsCommon::get_my_record();
		$defaults = array('serviceorder_manager'=>$me['id'], 'start_date'=>date('Y-m-d'));
		Utils_RecordBrowserCommon::mobile_rb('serviceorders',array('serviceorder_manager'=>$me['id']),array('serviceorder_name'=>'ASC'),array('customer'=>1,'status'=>1),$defaults);
	}
	
	public static function crm_calendar_handler($action) {
		$args = func_get_args();
		array_shift($args);
		$ret = null;
		switch ($action) {
			case 'get_all': $ret = call_user_func_array(array('ServiceOrdersCommon','crm_event_get_all'), $args);
							break;
			case 'update': $ret = call_user_func_array(array('ServiceOrdersCommon','crm_event_update'), $args);
							break;
			case 'get': $ret = call_user_func_array(array('ServiceOrdersCommon','crm_event_get'), $args);
							break;
			case 'delete': $ret = call_user_func_array(array('ServiceOrdersCommon','crm_event_delete'), $args);
							break;
			case 'new_event_types': $ret = array(array('label'=>__('Service Order'),'icon'=>Base_ThemeCommon::get_template_file('ServiceOrders','icon.png')));
							break;
			case 'new_event': $ret = call_user_func_array(array('ServiceOrdersCommon','crm_new_event'), $args);
							break;
			case 'view_event': $ret = call_user_func_array(array('ServiceOrdersCommon','crm_view_event'), $args);
							break;
			case 'edit_event': $ret = call_user_func_array(array('ServiceOrdersCommon','crm_edit_event'), $args);
							break;
			case 'recordset': $ret = 'serviceorders';
		}
		return $ret;
	}
	
	public static function crm_event_get_all($start, $end, $filter=null) {
		$start = date('Y-m-d',Base_RegionalSettingsCommon::reg2time($start));
		$crits = array();
		if ($filter===null) $filter = CRM_FiltersCommon::get();
		$f_array = explode(',',trim($filter,'()'));
		if($filter!='()' && $filter)
			$crits['('.'employees'] = $f_array;
		if ($customers && !empty($customers)) 
			$crits['|customer'] = $customers;
		elseif($filter!='()' && $filter) {
			$crits['|customer'] = $f_array;
			foreach ($crits['|customer'] as $k=>$v)
				$crits['|customer'][$k] = 'P:'.$v;
		}
		$crits['<=due_date'] = $end;
		$crits['>=due_date'] = $start;
		
		$ret = Utils_RecordBrowserCommon::get_records('serviceorders', $crits, array(), array(), CRM_CalendarCommon::$events_limit);

		$result = array();
		foreach ($ret as $r)
			$result[] = self::crm_event_get($r);

		return $result;
	}
	
	public static function crm_event_update($id, $start, $duration, $timeless) {
		if (!$timeless) return false;
		if (!Utils_RecordBrowserCommon::get_access('serviceorders','edit', self::get_serviceorder($id))) return false;
		$values = array('due_date'=>date('Y-m-d', $start));
		Utils_RecordBrowserCommon::update_record('serviceorders', $id, $values);
		return true;
	}
	
	public static function crm_event_get($id) {
		if (!is_array($id)) {
			$r = Utils_RecordBrowserCommon::get_record('serviceorders', $id);
		} else {
			$r = $id;
			$id = $r['id'];
		}

		$next = array('type'=>__('ServiceOrder'));
		
		$day = $r['due_date'];
		$iday = strtotime($day);
		$next['id'] = $r['id'];

		$base_unix_time = strtotime(date('1970-01-01 00:00:00'));
		$next['start'] = $iday;
		$next['timeless'] = $day;

		$next['duration'] = -1;
		$next['title'] = (string)$r['serviceorder_title'];
		$next['description'] = (string)$r['description'];
		$next['color'] = 'gray';
		

		$next['view_action'] = Utils_RecordBrowserCommon::create_record_href('serviceorders', $r['id'], 'view');
		$next['edit_action'] = Utils_RecordBrowserCommon::create_record_href('serviceorders', $r['id'], 'edit');


        $start_time = Base_RegionalSettingsCommon::time2reg($next['start'],2,false,false);
        $event_date = Base_RegionalSettingsCommon::time2reg($next['start'],false,3,false);

        $inf2 = array(
            __('Date')=>'<b>'.$event_date.'</b>');

		$emps = array();
		foreach ($r['employee'] as $e) {
			$e = CRM_ContactsCommon::contact_format_no_company($e, true);
			$e = str_replace('&nbsp;',' ',$e);
			if (mb_strlen($e,'UTF-8')>33) $e = mb_substr($e , 0, 30, 'UTF-8').'...';
			$emps[] = $e;
		}
		$inf2 += array(	__('ServiceOrder Name') => '<b>'.$next['serviceorder_title'].'</b>',
						__('Description') => $next['description'],
						__('Employee') => implode('<br>',$emps),
						__('Status') => Utils_CommonDataCommon::get_value('CRM/ServiceOrders_Status/'.$r['status']),
						__('Description / Notes') => Utils_AttachmentCommon::count('serviceorders/'.$r['id'])
					);

		$next['employees'] = $r['employees'];
		$next['status'] = $r['status'];
		$next['custom_tooltip'] = 
									'<center><b>'.
										__('ServiceOrder').
									'</b></center><br>'.
									Utils_TooltipCommon::format_info_tooltip($inf2).'<hr>'.
									CRM_ContactsCommon::get_html_record_info($r['created_by'],$r['created_on'],null,null);
		return $next;
	}
	
	public static function crm_event_delete($id) {
		Utils_RecordBrowserCommon::delete_record('serviceorders',$id);
		return true;
	}
	
	public static function crm_new_event($timestamp, $timeless, $id, $cal_obj) {
		$x = ModuleManager::get_instance('/Base_Box|0');
		if(!$x) trigger_error('There is no base box module instance',E_USER_ERROR);
		$me = CRM_ContactsCommon::get_my_record();
		$defaults = array('serviceorder_manager'=>$me['id'], 'status'=>0, 'permission'=>0, 'start_date'=>date('Y-m-d'));
		$defaults['due_date'] = date('Y-m-d', $timestamp);
		$x->push_main('Utils_RecordBrowser','view_entry',array('add', null, $defaults), 'serviceorders');
	}
	
	public static function crm_view_event($id, $cal_obj) {
		$rb = $cal_obj->init_module('Utils_RecordBrowser', 'serviceorders');
		$rb->view_entry('view', $id);
		return true;
	}
	public static function crm_edit_event($id, $cal_obj) {
		$rb = $cal_obj->init_module('Utils_RecordBrowser', 'serviceorders');
		$rb->view_entry('edit', $id);
		return true;
	}
}
?>
