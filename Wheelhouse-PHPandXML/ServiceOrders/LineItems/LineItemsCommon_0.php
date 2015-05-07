<?php
/**
 * Line Items Module
 * @Team Wheelhouse, CSUN Comp 380
 * @Developed 2014
 * @version 1.3.2
 */
 
defined("_VALID_ACCESS") || die('Direct access forbidden');

class ServiceOrders_LineItemsCommon extends ModuleCommon {

/*   public static function menu() {
   
      return array(__('Module') => array('__submenu__' => 1, __('Line Items') => array()));
      
   }
*/
   public static function serviceorders_addon_label() {
      return array('label' => __('Service Order Line Items'), 'show' => true);
   }
	
}

?>
