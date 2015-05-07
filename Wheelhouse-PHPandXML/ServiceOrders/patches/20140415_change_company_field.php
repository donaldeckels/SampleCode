<?php

$tab = 'serviceorders';

$cols = Utils_RecordBrowserCommon::init($tab);
if (!isset($cols['Customer']) && isset($cols['Company Name'])) {
    // create new field
    Utils_RecordBrowserCommon::new_record_field($tab, array(
        'name' => _M('Customer'),
        'type' => 'crm_company_contact',
        'required' => true,
        'param' => array('field_type' => 'multiselect'),
        'extra' => false,
        'visible' => true,
        'filter' => true,
        'position' => 'Company Name'
    ));

    // copy values
    $records = Utils_RecordBrowserCommon::get_records($tab);
    foreach ($records as $r) {
        $values = array('customer' => "C:" . $r['company_name']);
        Utils_RecordBrowserCommon::update_record($tab, $r['id'], $values, false, null, true);
    }

    // remove old field
    Utils_RecordBrowserCommon::delete_record_field($tab, 'Company Name');
}
?>