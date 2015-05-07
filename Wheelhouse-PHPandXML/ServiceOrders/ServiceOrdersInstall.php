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

class ServiceOrdersInstall extends ModuleInstall {
    const version = '3.3.3';

	public function install() {
		
		Base_ThemeCommon::install_default_theme($this->get_type());
		$fields = array(
			array('name' => _M('Service Order ID'),		'type'=>'calculated', 'required'=>false, 'param'=>Utils_RecordBrowserCommon::actual_db_type('text',16), 'extra'=>false, 'visible'=>true, 'display_callback'=>array('ServiceOrdersCommon','display_serviceorder_id')),
			array('name' => _M('ServiceOrder Name'), 	'type'=>'text', 'required'=>true, 'param'=>'64', 'extra'=>false, 'visible'=>true,'display_callback'=>array('ServiceOrdersCommon', 'display_so_name')),
            array('name' => _M('Customer'), 'type' => 'crm_company_contact', 'required' => true, 'param' => array('field_type' => 'multiselect'), 'extra' => false, 'visible' => true, 'filter' => true),
			array('name' => _M('ServiceOrder Manager'),'type'=>'crm_contact', 'param'=>array('field_type'=>'select', 'crits'=>array('ServiceOrdersCommon','serviceorders_employees_crits'), 'format'=>array('CRM_ContactsCommon','contact_format_no_company')), 'required'=>true, 'visible'=>true, 'extra'=>false,),
            array('name' => _M('Employees'), 'type' => 'crm_contact', 'required' => false, 'param' => array('field_type' => 'multiselect', 'crits' => array('ServiceOrdersCommon', 'serviceorders_employees_crits'), 'format'=>array('CRM_ContactsCommon','contact_format_no_company')), 'extra' => false, 'visible' => true),
			array('name' => _M('Status'), 		'type'=>'commondata', 'required'=>true, 'visible'=>true, 'filter'=>true, 'param'=>array('order_by_key'=>true,'ServiceOrders_Status'), 'extra'=>false),
			array('name' => _M('Start Date'), 	'type'=>'date', 'required'=>false, 'param'=>64, 'extra'=>false),
			array('name' => _M('Due Date'), 		'type'=>'date', 'required'=>false, 'param'=>64, 'extra'=>false),
			array('name' => _M('Vehicle'), 'type'=>'vehicles', 'required' => true, 'param' => array('field_type' => 'select'), 'extra' => false, 'visible' => true, 'filter' => true, 'display_callback'=>array('VehiclesCommon','display_vehicles')),
			array('name' => _M('Description / Notes'), 	'type'=>'long text', 'required'=>false, 'param'=>'250', 'extra'=>true)
		);

		Utils_RecordBrowserCommon::install_new_recordset('serviceorders', $fields);
		Utils_RecordBrowserCommon::new_filter('serviceorders', 'Status');
		
		Utils_RecordBrowserCommon::set_quickjump('serviceorders', 'ServiceOrder Name');
		Utils_RecordBrowserCommon::set_favorites('serviceorders', true);
		Utils_RecordBrowserCommon::set_recent('serviceorders', 15);
		Utils_RecordBrowserCommon::set_caption('serviceorders', _M('ServiceOrders'));
		Utils_RecordBrowserCommon::set_icon('serviceorders', Base_ThemeCommon::get_template_filename('ServiceOrders', 'icon.png'));
		Utils_RecordBrowserCommon::enable_watchdog('serviceorders', array('ServiceOrdersCommon','watchdog_label'));
		
// ************ addons ************** //
		Utils_AttachmentCommon::new_addon('serviceorders');
		Utils_RecordBrowserCommon::new_addon('contact', 'ServiceOrders', 'contact_serviceorders_addon', _M('ServiceOrders'));
		Utils_RecordBrowserCommon::new_addon('vehicles', 'ServiceOrders', 'vehicles_serviceorders_addon', _M('ServiceOrders'));

// ************ other ************** //	
		Utils_CommonDataCommon::new_array('ServiceOrders_Status',array(0=>_M('Scheduled'),1=>_M('Approved'),2=>_M('Canceled'),3=>_M('In Progress'),4=>_M('Completed'),5=>_M('On Hold')),true,true);
		CRM_CalendarCommon::new_event_handler(_M('ServiceOrders'), array('ServiceOrdersCommon', 'crm_calendar_handler'));
		
		Utils_RecordBrowserCommon::add_access('serviceorders', 'view', 'ACCESS:employee');
		Utils_RecordBrowserCommon::add_access('serviceorders', 'view', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('serviceorders', 'view', 'ACCESS:service_writer');
		Utils_RecordBrowserCommon::add_access('serviceorders', 'view', 'ACCESS:technician');
		
		Utils_RecordBrowserCommon::add_access('serviceorders', 'add', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('serviceorders', 'add', 'ACCESS:service_writer');
		// technician can add if scheduled
		Utils_RecordBrowserCommon::add_access('serviceorders', 'add', 'ACCESS:technician', array('status'=>0));
		
		// technician can edit if status is approved or in progress
		Utils_RecordBrowserCommon::add_access('serviceorders', 'edit', 'ACCESS:technician', array('status'=>1));
		Utils_RecordBrowserCommon::add_access('serviceorders', 'edit', 'ACCESS:technician', array('status'=>3));
		// Service Writer can edit if status is scheduled
		Utils_RecordBrowserCommon::add_access('serviceorders', 'edit', 'ACCESS:service_writer', array('status'=>0));
		Utils_RecordBrowserCommon::add_access('serviceorders', 'edit', 'ACCESS:manager');
		
 		Utils_RecordBrowserCommon::add_access('serviceorders', 'delete', 'ACCESS:manager');
		
		return true;
	}
	
	public function uninstall() {
		CRM_CalendarCommon::delete_event_handler('ServiceOrders');
		Base_ThemeCommon::uninstall_default_theme($this->get_type());
		Utils_AttachmentCommon::delete_addon('serviceorders');
		Utils_RecordBrowserCommon::delete_addon('contact', 'ServiceOrders', 'contact_serviceorders_addon');
		Utils_RecordBrowserCommon::delete_addon('vehicles', 'ServiceOrders', 'vehicles_serviceorders_addon');
		Utils_RecordBrowserCommon::uninstall_recordset('serviceorders');
		Utils_CommonDataCommon::remove('ServiceOrders_Status');
		return true;
	}
	
	public function version() {
		return array(self::version);
	}
	
	public function requires($v) {
		return array(
			array('name'=>'Base','version'=>0),
			array('name'=>'Utils/ChainedSelect', 'version'=>0), 
			array('name'=>'CRM/Contacts','version'=>0),
			array('name'=>'Vehicles','version'=>0));
	}
	
	public static function info() {
		return array(
			'Description'=>'ServiceOrders Management',
			'Author'=>'Team Wheelhouse',
			'License'=>'MIT');
	}
	
    public static function simple_setup() {
        return array('package'=>__('WheelHouse'), 'option'=>__('ServiceOrders'));
    }
}

?>
