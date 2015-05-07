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

class VehiclesInstall extends ModuleInstall {
    const version = '1.4.2';

	public function install() {
		Base_ThemeCommon::install_default_theme($this->get_type());
		Utils_RecordBrowserCommon::register_datatype('vehicles', 'VehiclesCommon', 'vehicles_datatype');
		$fields = array(
			array('name' => _M('VIN'), 	'type'=>'text', 'required'=>true, 'param'=>'64', 'extra'=>false, 'visible'=>true,'display_callback'=>array('VehiclesCommon', 'display_vin'), 'filter'=>true),
            array('name' => _M('License Plate'),	'type'=>'text', 'required' =>true, 'param'=>'9', 'extra'=>false, 'visible'=>true, 'display_callback'=>array('VehiclesCommon', 'display_plate'), 'filter'=>true),
			array('name' => _M('State/Region'), 'type'=>'text', 'required' => true, 'param'=>'20', 'extra'=>false, 'visible' => true, 'filter' => true),
			array('name' => _M('Owner'), 'type' => 'crm_company_contact', 'required' => true, 'param' => array('field_type' => 'select'), 'extra' => false, 'visible' => true, 'filter' => true),
			array('name' => _M('Year'), 'type' => 'text', 'required' => true, 'param'=>'4', 'extra' => false, 'visible' => true, 'filter' => true),
			array('name' => _M('Make'), 'type' => 'text', 'required' => true, 'param'=>'20', 'extra' => false, 'visible' => true, 'filter' => true),
			array('name' => _M('Model'), 'type' => 'text', 'required' => true, 'param'=>'20', 'extra' => false, 'visible' => true, 'filter' => true),
			array('name' => _M('Color'), 'type' => 'text', 'required' => true, 'param'=>'15', 'extra' => false, 'visible' => true, 'filter' => true),
			array('name' => _M('Package'), 'type' => 'text', 'required' => false, 'param'=>'20', 'extra' => false, 'visible' => true, 'filter' => true),
			array('name' => _M('Mileage'), 'type' => 'float', 'required' => true, 'param'=>'8', 'extra' => false, 'visible' => true, 'filter' => true),
			array('name' => _M('Notes'), 	'type'=>'long text', 'required'=>false, 'param'=>'250', 'extra'=>true, 'visible' => true, 'filter' => false)
		);

		Utils_RecordBrowserCommon::install_new_recordset('vehicles', $fields);
		
		//Utils_RecordBrowserCommon::register_processing_callback($vehicles, $callback);
		//Utils_RecordBrowserCommon::set_processing_callback('vehicles', array('VehiclesCommon', 'submit_vehicles'));
		Utils_RecordBrowserCommon::set_quickjump('vehicles', 'VIN');
		Utils_RecordBrowserCommon::set_favorites('vehicles', true);
		Utils_RecordBrowserCommon::set_recent('vehicles', 15);
		Utils_RecordBrowserCommon::set_caption('vehicles', _M('Vehicles'));
		Utils_RecordBrowserCommon::set_icon('vehicles', Base_ThemeCommon::get_template_filename('Vehicles', 'icon.png'));
		Utils_RecordBrowserCommon::enable_watchdog('vehicles', array('VehiclesCommon','watchdog_label'));
		//Utils_RecordBrowserCommon::set_QFfield_callback('vehicles','VIN',array('VehiclesCommon','QFfield_vehicles'));
		
// ************ addons ************** //
		Utils_RecordBrowserCommon::new_addon('contact', 'Vehicles', 'contact_vehicles_addon', _M('Vehicles'));
		Utils_AttachmentCommon::new_addon('vehicles');

// ************ other ************** //	
		
		Utils_CommonDataCommon::extend_array('Contacts/Access',array('technician'=>_M('Technician')));
		Utils_CommonDataCommon::extend_array('Contacts/Access',array('service_writer'=>_M('Service Writer')));
		
		Utils_RecordBrowserCommon::add_access('vehicles', 'view', 'ACCESS:employee');
		Utils_RecordBrowserCommon::add_access('vehicles', 'view', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('vehicles', 'view', 'ACCESS:service_writer');
		Utils_RecordBrowserCommon::add_access('vehicles', 'view', 'ACCESS:technician');
		
		Utils_RecordBrowserCommon::add_access('vehicles', 'add', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('vehicles', 'add', 'ACCESS:service_writer');
		
		Utils_RecordBrowserCommon::add_access('vehicles', 'edit', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('vehicles', 'edit', 'ACCESS:service_writer');
		
 		Utils_RecordBrowserCommon::add_access('vehicles', 'delete', 'ACCESS:manager');
		
		return true;
	}
	
	public function uninstall() {
		Base_ThemeCommon::uninstall_default_theme($this->get_type());
		Utils_AttachmentCommon::delete_addon('vehicles');
		Utils_RecordBrowserCommon::delete_addon('company', 'Vehicles', 'company_vehicles_addon');
		Utils_RecordBrowserCommon::uninstall_recordset('vehicles');
		DB::execute('DELETE FROM recordbrowser_datatype WHERE type="vehicles"');
		return true;
	}
	
	public function version() {
		return array(self::version);
	}
	
	public function requires($v) {
		return array(
			array('name'=>'Base','version'=>0),
			array('name'=>'Utils/ChainedSelect', 'version'=>0), 
			array('name'=>'CRM/Contacts','version'=>0));
	}
	
	public static function info() {
		return array(
			'Description'=>'Vehicles Management',
			'Author'=>'Team Wheelhouse',
			'License'=>'MIT');
	}
	
    public static function simple_setup() {
        return array('package'=>__('WheelHouse'));
    }
	
/*	public static function install_permissions() {
		Utils_RecordBrowserCommon::wipe_access('vehicles');
		Utils_RecordBrowserCommon::add_access('vehicles', 'print', 'SUPERADMIN');
		Utils_RecordBrowserCommon::add_access('vehicles', 'export', 'SUPERADMIN');
		Utils_RecordBrowserCommon::add_access('vehicles', 'view', 'ACCESS:employee', array('(!permission'=>2, '|:Created_by'=>'USER_ID'));
		Utils_RecordBrowserCommon::add_access('vehicles', 'view', 'ALL', array('login'=>'USER_ID'));
		Utils_RecordBrowserCommon::add_access('vehicles', 'add', 'ACCESS:employee');
		Utils_RecordBrowserCommon::add_access('vehicles', 'edit', 'ACCESS:employee', array('(permission'=>0, '|:Created_by'=>'USER_ID'), array('access', 'login'));
		Utils_RecordBrowserCommon::add_access('vehicles', 'edit', 'ALL', array('login'=>'USER_ID'), array('company_name', 'related_companies', 'access', 'login', 'group', 'permission'));
		Utils_RecordBrowserCommon::add_access('vehicles', 'edit', array('ALL','ACCESS:manager'), array('company_name'=>'USER_COMPANY'), array('login', 'company_name', 'related_companies'));
		Utils_RecordBrowserCommon::add_access('vehicles', 'edit', array('ACCESS:employee','ACCESS:manager'), array());
		Utils_RecordBrowserCommon::add_access('vehicles', 'delete', 'ACCESS:employee', array(':Created_by'=>'USER_ID'));
		Utils_RecordBrowserCommon::add_access('vehicles', 'delete', array('ACCESS:manager'));
	} */
}

?>
