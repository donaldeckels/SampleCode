<?php
/**
 * Line Items Module
 * @Team Wheelhouse, CSUN Comp 380
 * @Developed 2014
 * @version 1.3.2
 */
 
defined("_VALID_ACCESS") || die('Direct access forbidden');
 
class ServiceOrders_LineItems_Recordset extends RBO_Recordset {
 
    function table_name() { // - choose a name for the table that will be stored in EPESI database
 
        return 'LineItems';
 
    }
 
	function fields() { // - here you choose the fields to add to the record browser
 		$fields = array();
			
		$category_name = new RBO_Field_Text(_M('Service Order ID')); //'Name'
		$category_name->set_length(24)->set_required()->set_visible();
		$fields[] = $category_name;
		
		$description = new RBO_Field_LongText(_M('Description'));
		$description->set_visible();
		$fields[] = $description;
 
		$CommonData = new RBO_Field_CommonData('Status','LineItems_Status');
		$CommonData->set_required()->set_visible();
		$fields[] = $CommonData;
		
		$MultiSelect = new RBO_Field_MultiSelect('Parts');
		$MultiSelect->from('parts')->fields('part_number','part_name')->set_visible();
		$fields[] = $MultiSelect;
		
      return $fields;
 
    }
}
?>