<?php
/**
 * Line Items Module
 * @Team Wheelhouse, CSUN Comp 380
 * @Developed 2014
 * @version 1.3.2
 */
 
defined("_VALID_ACCESS") || die('Direct access forbidden');

class ServiceOrders_LineItems extends Module {

   public function body() {
      
		// call record browser
		
		$rs = new ServiceOrders_LineItems_Recordset();
		$this->rb = $rs->create_rb_module($this, 'ServiceOrders_LineItems');
		$this->display_module($this->rb);
   }

   public function serviceorders_addon($arg){
		$rb = $this->init_module('Utils/RecordBrowser','LineItems');
		// filter criteria
		//$padID = ''.str_pad($arg['id'], 4, '0', STR_PAD_LEFT);
		$padID = 'SO#'.str_pad($arg['id'], 6, '0', STR_PAD_LEFT);
      $item = array(array('service_order_id'=>$padID));  
		// new record default value
      $rb->set_defaults(array('service_order_id'=>	$padID)); //$arg['id'], 'name'
	   $this->display_module($rb,$item,'show_data');
   }

/*
   public function serviceorders_addon($record) {
		$this->init_default_rb();

		$crits = array('Name' => $record['service_order_name']);
		$cols = array('Description' => true);
		$show_data_params = array($crits, $cols);
		
		//$rb->set_defaults(array('Name'=>$record['service_order_name']));

		$this->rb->set_defaults(array('Name'=>$record['service_order_name']));
		
		$this->display_module($this->rb, $show_data_params, 'show_data');
   }

	private function init_default_rb() {
		$rs = new ServiceOrders_LineItems_Recordset();
		$this->rb = $rs->create_rb_module($this);
	}
*/
}

?>