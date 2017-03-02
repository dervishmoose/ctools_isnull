<?php

/**
 * @file
 * Plugin to check if the title has configured string.
 */

$plugin = array(
  'title' => t('Field is null'),
  'description' => t('Checks if field is null.'),
  'callback' => 'ctool_isnull_ctools_access_check',
  'default' => array('negate' => 0),
  'summary' => 'ctool_isnull_ctools_access_summary',
  'settings form' => 'ctool_isnull_ctools_access_settings',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Settings form for the 'title hide' access plugin.
 */
function ctool_isnull_ctools_access_settings($form, &$form_state, $conf) {
  $fields = array_keys (field_read_fields(array('entity_type' => 'node')));
// cheap way to make the keys and the values the same
  $fields_value =array_combine ( $fields , $fields );

  $form['settings']['keyword'] = array(
    '#title' => t('Keyword'),
    '#type' => 'select',
    '#description' => t('Select field you would like to check for null.'),
    '#default_value' => $conf['keyword'],
    '#required' => TRUE,
    '#options' => $fields_value,
  );


  return $form;
}


/**
 * Check for access.
 */
function ctool_isnull_ctools_access_check($conf, $context) {

  // Return false if context is not set.
  if (empty($context) || empty($context->data)) {
    return FALSE;
  }

  $node = $context->data;

//  return FALSE;
  if (empty($node->$conf['keyword'])) {

    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Provide a summary description.
 */
function ctool_isnull_ctools_access_summary($conf, $context) {
  $replacement = array('@keyword' => $conf['keyword']);
  return t('Checks if "@keyword" is null.', $replacement);
}
