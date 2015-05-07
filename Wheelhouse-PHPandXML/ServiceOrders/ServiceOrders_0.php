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

class ServiceOrders extends Module {
	private $rb;

public function body() {
		// serviceorders=recordset, serviceorders_module=internal unique name for RB
		$this->rb = $this->init_module('Utils/RecordBrowser','serviceorders','serviceorders_module');
		// set defaults
		$sts = Utils_CommonDataCommon::get_translated_array('ServiceOrders_Status');
		$trans = array('__NULL__'=>array(), '__ALLACTIVE__'=>array('!status'=>array(0,2,4,5)));
		foreach ($sts as $k=>$v)
			$trans[$k] = array('status'=>$k);
		$me = CRM_ContactsCommon::get_my_record();
		$this->rb->set_custom_filter('status',array('type'=>'select','label'=>__('ServiceOrders status'),'args'=>array('__NULL__'=>'['.__('All').']','__ALLACTIVE__'=>'['.__('All active').']')+$sts,'trans'=>$trans));
		$this->rb->set_defaults(array('serviceorder_manager'=>$me['id'], 'start_date'=>date('Y-m-d')));
		$this->rb->set_filters_defaults(array('status'=>'__ALL__'));
		$this->rb->set_default_order(array('serviceorder_name'=>'ASC'));		

        $fcallback = array('CRM_ContactsCommon','autoselect_company_contact_format');
        $this->rb->set_custom_filter('customer', array('type'=>'autoselect','label'=>__('Customer'),'args'=>array(), 'args_2'=>array(array('CRM_ContactsCommon','auto_company_contact_suggestbox'), array($fcallback)), 'args_3'=>$fcallback, 'trans_callback'=>array('CRM_ContactsCommon','autoselect_contact_filter_trans')));        
		$this->display_module($this->rb);
		$this->set_module_variable('ID', 1);
	}

public function applet($conf, & $opts) {
		$opts['go'] = true; // enable full screen
		$sts = Utils_CommonDataCommon::get_translated_array('ServiceOrders_Status');
		$rb = $this->init_module('Utils/RecordBrowser','serviceorders','serviceorders');
		$limit = null;
		$crits = array();
		$me = CRM_ContactsCommon::get_my_record();
		if ($conf['status']=='__ALL__') {
			$opts['title'] = __('All ServiceOrders');
		} elseif ($conf['status']=='__NULL__') {
			$opts['title'] = __('Active serviceorders');
			$crits['!status'] = array(2,4);
		} else {
			$projstatus = $sts[$conf['status']];
			$opts['title'] = __('ServiceOrders: %s',array($projstatus));
			$crits['status'] = $conf['status'];
		}
		if ($conf['my']==1) {
			$crits['serviceorder_manager'] = array($me['id']);
		}

		// $conds - parameters for the applet
		// 1st - table field names, width, truncate
		// 2nd - criteria (filter)
		// 3rd - sorting
		// 4th - function to return tooltip
		// 5th - limit how many records are returned, null = no limit
		// 6th - Actions icons - default are view + info (with tooltip)
		
		$sorting = array('serviceorder_name'=>'ASC');
		$cols = array(
							array('field'=>'serviceorder_name', 'width'=>10),
							array('field'=>'customer', 'width'=>10)
										);

		$conds = array(
									$cols,
									$crits,
									$sorting,
									array('ServiceOrdersCommon','applet_info_format'),
									$limit,
									$conf,
									& $opts
				);
		$opts['actions'][] = Utils_RecordBrowserCommon::applet_new_record_button('serviceorders',array('serviceorder_manager'=>$me['id'], 'start_date'=>date('Y-m-d')));
		$this->display_module($rb, $conds, 'mini_view');
	}

/*public function company_serviceorders_addon($arg){
		$rb = $this->init_module('Utils/RecordBrowser','serviceorders');
		$rb->set_defaults(array('customer'=>array('C:'.$arg['id'])));
		$proj = array(array('customer'=>'C:'.$arg['id']), array('customer' => false), array('Fav'=>'DESC'));
		$this->display_module($rb,$proj,'show_data');
	}*/

    public function contact_serviceorders_addon($arg) {
        $rb = $this->init_module('Utils/RecordBrowser', 'serviceorders');
        $defaults = array('customer' => array('P:' . $arg['id']));
        $multiple = false;
        // check if it's employee
        $main_company = CRM_ContactsCommon::get_main_company();
        if ($arg['company_name'] == $main_company
                || array_search($main_company, $arg['related_companies']) !== false) {
            $defaults = array(
                _M('Contact as customer') => array('icon' => null, 'defaults' => $defaults),
                _M('Contact as service order manager') => array('icon' => null, 'defaults' => array('serviceorder_manager' => array($arg['id']))),
                _M('Contact as employee') => array('icon' => null, 'defaults' => array('employees' => array($arg['id'])))
            );
            $multiple = true;
        }
        $rb->set_defaults($defaults, $multiple);
        $proj = array(array('(customer' => 'P:' . $arg['id'], '|serviceorder_manager' => $arg['id'], '|employees' => $arg['id']), array(), array('Fav' => 'DESC'));
        $this->display_module($rb, $proj, 'show_data');
    }
	
	public function vehicles_serviceorders_addon($arg){
		$rb = $this->init_module('Utils/RecordBrowser','serviceorders');
		$rb->set_defaults(array('vehicle'=>array('C:'.$arg['id'])));
		$proj = array(array('vehicle'=>'C:'.$arg['id']), array('vehicle' => true), array('Fav'=>'DESC'));
		$this->display_module($rb,$proj,'show_data');
	}

    public function caption(){
		if (isset($this->rb)) return $this->rb->caption();
	}
	
	
}

?>