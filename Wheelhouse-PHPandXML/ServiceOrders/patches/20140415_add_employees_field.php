<?php

Utils_RecordBrowserCommon::new_record_field('serviceorders', array(
    'name' => _M('Employees'),
    'type' => 'crm_contact',
    'required' => false,
    'param' => array('field_type' => 'multiselect', 'crits' => array('CRM_ContactsCommon', 'employee_crits')),
    'extra' => false,
    'visible' => true,
    'filter' => true,
    'position' => 'Service Order Manager'
));
?>