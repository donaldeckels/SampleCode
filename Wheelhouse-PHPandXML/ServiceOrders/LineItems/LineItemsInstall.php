<?php
/**
 * Line Items Module
 * @Team Wheelhouse, CSUN Comp 380
 * @Developed 2014
 * @version 1.3.2
 */
 
defined("_VALID_ACCESS") || die('Direct access forbidden');

class ServiceOrders_LineItemsInstall extends ModuleInstall {

   public function install() {
      Base_ThemeCommon::install_default_theme($this->get_type());
      $fields = new ServiceOrders_LineItems_Recordset();
      $success = $fields->install();
      //$fields->add_default_access();
      $fields->set_caption(_M('Line Items'));
		
      Utils_RecordBrowserCommon::new_addon('serviceorders', $this->get_type(), 'serviceorders_addon',
      array($this->get_type() . 'Common', 'serviceorders_addon_label'));
		
		// line item status values
		Utils_CommonDataCommon::new_array('LineItems_Status',array(0=>_M('Requested'),1=>_M('Approved'),2=>_M('Canceled'),3=>_M('In Progress'),4=>_M('Completed')));
		
		Utils_RecordBrowserCommon::add_access('LineItems', 'view', 'ACCESS:employee');
		Utils_RecordBrowserCommon::add_access('LineItems', 'view', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('LineItems', 'view', 'ACCESS:service_writer');
		Utils_RecordBrowserCommon::add_access('LineItems', 'view', 'ACCESS:technician');
		
		Utils_RecordBrowserCommon::add_access('LineItems', 'add', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('LineItems', 'add', 'ACCESS:service_writer');
		// technician can add if scheduled
		Utils_RecordBrowserCommon::add_access('LineItems', 'add', 'ACCESS:technician', array('status'=>0));
		// technician can edit if status is approved or in progress
		
		Utils_RecordBrowserCommon::add_access('LineItems', 'edit', 'ACCESS:technician', array('status'=>1));
		Utils_RecordBrowserCommon::add_access('LineItems', 'edit', 'ACCESS:technician', array('status'=>3));
		// Service Writer can edit if status is scheduled
		Utils_RecordBrowserCommon::add_access('LineItems', 'edit', 'ACCESS:service_writer', array('status'=>0));
		Utils_RecordBrowserCommon::add_access('LineItems', 'edit', 'ACCESS:manager');
		
 		Utils_RecordBrowserCommon::add_access('LineItems', 'delete', 'ACCESS:manager');
	
      return true;
   }

   public function uninstall() {
      Base_ThemeCommon::uninstall_default_theme($this->get_type());
      $fields = new ServiceOrders_LineItems_Recordset();
      $success = $fields->uninstall();
			
      Utils_RecordBrowserCommon::delete_addon('serviceorders', $this->get_type(), 'serviceorders_addon');
		
		Utils_CommonDataCommon::remove('LineItems_Status');
		
      return true;
   }

   public function info() {
   
      return array(
         'Description'=>'Service Orders - Line Items',
         'Author'=>'Team WheelHouse',
         'License'=>'MIT');
   }

/*   public function simple_setup() {
   
      return array('package'=> __('LineItems'), 'version'=>'1.2.1');
      
   }
*/

	public static function simple_setup() {
       return array('package'=>__('WheelHouse'), 'option'=>__('ServiceOrders'));
   }


	public function requires($v) {
		return array(
			array('name'=>'ServiceOrders','version'=>0),
	    	array('name'=>'Parts','version'=>0));
	}
   
   public function version() {
   
      return array('1.3.2');
      
   }
   
}

?>
