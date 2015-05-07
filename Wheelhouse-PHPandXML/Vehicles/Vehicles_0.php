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

class Vehicles extends Module {
	private $rb;

public function body() {
		// vehicles=recordset, vehicles_module=internal unique name for RB
		$this->rb = $this->init_module('Utils/RecordBrowser','vehicles','vehicles_module');
		// set defaults
		$this->rb->set_defaults(array('Country'=>"United States"));
		$this->rb->set_default_order(array('vehicles_name'=>'ASC'));

        $fcallback = array('CRM_ContactsCommon','autoselect_company_contact_format');
        $this->rb->set_custom_filter('customer', array('type'=>'autoselect','label'=>__('Customer'),'args'=>array(), 'args_2'=>array(array('CRM_ContactsCommon','auto_company_contact_suggestbox'), array($fcallback)), 'args_3'=>$fcallback, 'trans_callback'=>array('CRM_ContactsCommon','autoselect_contact_filter_trans')));        
		$this->display_module($this->rb);
	}

public function applet($conf, & $opts) {
		$opts['go'] = true; // enable full screen
		$rb = $this->init_module('Utils/RecordBrowser','vehicles','vehicles');
		$limit = null;
		$crits = array();
		$me = CRM_ContactsCommon::get_my_record();
		if ($conf['status']=='__ALL__') {
			$opts['title'] = __('All Vehicles');
		}
		if ($conf['my']==1) {
			$crits['vehicles_manager'] = array($me['id']);
		}

		// $conds - parameters for the applet
		// 1st - table field names, width, truncate
		// 2nd - criteria (filter)
		// 3rd - sorting
		// 4th - function to return tooltip
		// 5th - limit how many records are returned, null = no limit
		// 6th - Actions icons - default are view + info (with tooltip)
		
		$sorting = array('license_plate'=>'ASC');
		$cols = array(
							array('field'=>'license_plate', 'width'=>10),
							array('field'=>'owner', 'width'=>10)
										);

		$conds = array(
									$cols,
									$crits,
									$sorting,
									array('VehiclesCommon','applet_info_format'),
									$limit,
									$conf,
									& $opts
				);
		$opts['actions'][] = Utils_RecordBrowserCommon::applet_new_record_button('vehicles',array('vehicles_manager'=>$me['id'], 'start_date'=>date('Y-m-d')));
		$this->display_module($rb, $conds, 'mini_view');
	}

    public function contact_vehicles_addon($arg) {
        $rb = $this->init_module('Utils/RecordBrowser', 'vehicles');
        $defaults = array('owner' => array('P:' . $arg['id']));
        $multiple = false;
    
        $rb->set_defaults($defaults, $multiple);
        $proj = array(array('owner' => 'P:' . $arg['id']), array(), array('Fav' => 'DESC'));
        $this->display_module($rb, $proj, 'show_data');
    }

    public function caption(){
		if (isset($this->rb)) return $this->rb->caption();
	}
}

?>