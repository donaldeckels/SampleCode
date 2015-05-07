<?php

/**
 * Description of Parts_0
 * WheelHouse Parts Module
 * @author Team WheelHouse
  * @version 1.5.2
 */
defined("_VALID_ACCESS") || die();
class Parts extends Module{
    private $rb = null;
    
    public function body() {
		// parts=recordset, parts_module=internal unique name for RB
		$this->rb = $this->init_module('Utils/RecordBrowser','parts','parts_module');
		// set defaults
		
                $me = CRM_ContactsCommon::get_my_record();
		$this->rb->set_defaults(array('parts_manager'=>$me['id']));
		$this->rb->set_filters_defaults(array('status'=>'__ALLACTIVE__'));
		$this->rb->set_default_order(array('parts_name'=>'ASC'));		

       // $fcallback = array('CRM_ContactsCommon','autoselect_company_contact_format');
        //$this->rb->set_custom_filter('customer', array('type'=>'autoselect','label'=>__('Customer'),'args'=>array(), 'args_2'=>array(array('CRM_ContactsCommon','auto_company_contact_suggestbox'), array($fcallback)), 'args_3'=>$fcallback, 'trans_callback'=>array('CRM_ContactsCommon','autoselect_contact_filter_trans')));        
		$this->display_module($this->rb);
	}

public function applet($conf, & $opts) {
		$opts['go'] = true; // enable full screen
		$rb = $this->init_module('Utils/RecordBrowser','parts','parts');
		$limit = null;
		$crits = array();
		$me = CRM_ContactsCommon::get_my_record();
		
		if ($conf['my']==1) {
			$crits['parts_manager'] = array($me['id']);
		}

		// $conds - parameters for the applet
		// 1st - table field names, width, truncate
		// 2nd - criteria (filter)
		// 3rd - sorting
		// 4th - function to return tooltip
		// 5th - limit how many records are returned, null = no limit
		// 6th - Actions icons - default are view + info (with tooltip)
		
		$sorting = array('parts_name'=>'ASC');
		$cols = array(
                            array('field'=>'parts_name', 'width'=>10),
                            array('field'=>'customer', 'width'=>10)
                                                    );

		$conds = array(
                                            $cols,
                                            $crits,
                                            $sorting,
                                            array('PartsCommon','applet_info_format'),
                                            $limit,
                                            $conf,
                                            & $opts
                                );
		$opts['actions'][] = Utils_RecordBrowserCommon::applet_new_record_button('parts',array('parts_manager'=>$me['id']));
		$this->display_module($rb, $conds, 'mini_view');
	}

public function company_parts_addon($arg){
		$rb = $this->init_module('Utils/RecordBrowser','parts');
		$rb->set_defaults(array('customer'=>array('C:'.$arg['id'])));
		$proj = array(array('customer'=>'C:'.$arg['id']), array('customer' => false), array('Fav'=>'DESC'));
		$this->display_module($rb,$proj,'show_data');
	}

    public function contact_parts_addon($arg) {
        $rb = $this->init_module('Utils/RecordBrowser', 'parts');
        $defaults = array('customer' => array('P:' . $arg['id']));
        $multiple = false;
        // check if it's employee
        $main_company = CRM_ContactsCommon::get_main_company();
        if ($arg['company_name'] == $main_company
                || array_search($main_company, $arg['related_companies']) !== false) {
            $defaults = array(
                _M('Contact as customer') => array('icon' => null, 'defaults' => $defaults),
                _M('Contact as service order manager') => array('icon' => null, 'defaults' => array('parts_manager' => array($arg['id']))),
                _M('Contact as employee') => array('icon' => null, 'defaults' => array('employees' => array($arg['id'])))
            );
            $multiple = true;
        }
        $rb->set_defaults($defaults, $multiple);
        $proj = array(array('(customer' => 'P:' . $arg['id'], '|parts_manager' => $arg['id'], '|employees' => $arg['id']), array(), array('Fav' => 'DESC'));
        $this->display_module($rb, $proj, 'show_data');
    }

    public function caption(){
		if (isset($this->rb)) return $this->rb->caption();
	}
}
