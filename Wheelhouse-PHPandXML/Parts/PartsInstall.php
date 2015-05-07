<?php

/**
 * This class provides initialization data for CRMHR module.
 * 
 * WheelHouse Parts Module
 * @author Team WheelHouse
  * @version 1.5.2
 */

//me thinks i can try to run this one
defined("_VALID_ACCESS") || die();
class PartsInstall extends ModuleInstall
{
    const version = '1.5.2';
    public function install() 
    {
        Base_LangCommon::install_translations($this->get_type());

        Base_ThemeCommon::install_default_theme($this->get_type());
        $fields = array(
                        array('name' => _M('SKU ID'),		'type'=>'calculated', 'required'=>false, 'param'=>Utils_RecordBrowserCommon::actual_db_type('text',16), 'extra'=>false, 'visible'=>true, 'display_callback'=>array('PartsCommon','display_SKU')),
			array('name' => _M('Part Name'), 	'type'=>'text', 'required'=>true, 'param'=>'64', 'extra'=>false, 'visible'=>true,'display_callback'=>array('PartsCommon', 'display_part_name')),
                        array('name' => _M('Part Number'), 'type' => 'text', 'required' => true, 'param'=>'16', 'extra' => false, 'visible' => true, 'filter' => true,'display_callback'=>array('PartsCommon', 'display_partNum')),            
                        array('name' => _M('Vendor'), 'type' => 'crm_company', 'required' => false, 'param' => array('field_type' => 'multiselect'), 'extra' => false, 'visible' => true, 'filter' => true),
			array('name' => _M('Part Information'),	'type'=>'long text', 'required' =>false, 'param'=>'250', 'extra'=>false),
            		array('name' => _M('Price'), 'type' => 'currency', 'required' => true, 'param'=>'8', 'extra' => false, 'visible' => true, 'filter' => true,'display_callback'=>array('PartsCommon', 'display_price')),
                        array('name' => _M('Manufacturer'), 	'type'=>'text', 'required'=>false, 'param'=>'64', 'extra'=>true, 'visible'=>true,'display_callback'=>array('PartsCommon', 'display_brand'))
		);

		Utils_RecordBrowserCommon::install_new_recordset('parts', $fields);		
		Utils_RecordBrowserCommon::set_quickjump('parts', 'Part Name');
		Utils_RecordBrowserCommon::set_favorites('parts', true);
		Utils_RecordBrowserCommon::set_recent('parts', 15);
		Utils_RecordBrowserCommon::set_caption('parts', _M('Parts'));
		Utils_RecordBrowserCommon::set_icon('parts', Base_ThemeCommon::get_template_filename('Parts', 'icon.png'));
		Utils_RecordBrowserCommon::enable_watchdog('parts', array('PartsCommon','watchdog_label'));
		Utils_RecordBrowserCommon::register_datatype('parts', 'PartsCommon', 'parts_datatype');
		
		
// ************ addons ************** //
		Utils_AttachmentCommon::new_addon('parts');
		Utils_RecordBrowserCommon::new_addon('company', 'Parts', 'company_parts_addon', _M('Parts'));
		Utils_RecordBrowserCommon::new_addon('contact', 'Parts', 'contact_parts_addon', _M('Parts'));

// ************ other ************** //			
		Utils_RecordBrowserCommon::add_access('parts', 'view', 'ACCESS:employee');
		Utils_RecordBrowserCommon::add_access('parts', 'view', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('parts', 'view', 'ACCESS:service_writer');
		Utils_RecordBrowserCommon::add_access('parts', 'view', 'ACCESS:technician');
		
		Utils_RecordBrowserCommon::add_access('parts', 'add', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('parts', 'add', 'ACCESS:service_writer');
		
		Utils_RecordBrowserCommon::add_access('parts', 'edit', 'ACCESS:manager');
		Utils_RecordBrowserCommon::add_access('parts', 'edit', 'ACCESS:service_writer');
		
 		Utils_RecordBrowserCommon::add_access('parts', 'delete', 'ACCESS:manager');
		
		return true;
	}
	
	public function uninstall() {
		Base_ThemeCommon::uninstall_default_theme($this->get_type());
		Utils_AttachmentCommon::delete_addon('parts');
		Utils_RecordBrowserCommon::delete_addon('company', 'Parts', 'company_parts_addon');
		Utils_RecordBrowserCommon::uninstall_recordset('parts');
		DB::execute('DELETE FROM recordbrowser_datatype WHERE type="parts"');
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
			'Description'=>'Manages Stock',
			'Author'=>'Team Wheelhouse',
			'License'=>'MIT');
	}
	
    public static function simple_setup() {
        return array('package'=>__('WheelHouse'));
    }
}
?>
