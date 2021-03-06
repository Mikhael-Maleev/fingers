<?php

/**
*@file
*�������� ������ ���������������� �������� ��� ������ �������������.
*/

/**
*	�������� �����. ��������� ������������.
*@ingroup forms
*@see system_settings_form().
*/


function annotate_admin_settings(){
	// ��������� ������� ����� ���: ����� - ��� ��������� �����,
	// � ��������  - "������������� �����". ��������:
	// array('page' => 'Basic page','article' => 'Articles')
	$types = node_type_get_types();
	foreach($types as $node_type){
		$options[$node_type->type] = $node_type->name;
	}
	$form['annotate_node_types'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Users may annotate these content type'), // ������������ ����� ������������ ��� ���� ��������
		'#options' => $options,
		'#default_value' => variable_get('annotate_node_types',array('page')),
		'#description' => t('A text field will be available on this content types to make author-spesific notes.')// ��� ���� ����� �������� ����� �������� ��������� ����, ���������������� ��� ��������� �������
	);
	$form['annotate_deletion'] = array(
		'#type' => 'radios',
		'#title' => t('Annotations will be deleted'),//�������� ����� �������
		'#description' => t('Select a metod for deleting annotations.'),// �������� ����� ��� �������� ���������
		'#options' => array(
			t('Never'), //�������
			t('Randomly'), //��������� �������
			t('After 30 days') //������ 30 ����
		),
		'#default_value' => variable_get('annotate_deletion',0)//�� ��������� �������
	);
	$form['annotate_limit_per_node'] = array(
		'#type' => 'textfield',
		'#title' => t('Annotations per node'),//�������� � ����
		'#description' => t('Enter the maximum number of annotations allowed per node (0 for no limit).'),// �������� ������������ ����������� ��������� � ���� (0 �� ����������)
		'#default_value' => variable_get('annotate_limit_per_node',1),//�� ��������� �������
		'#size' => 3
	);
	return system_settings_form($form, TRUE);
}

function annotate_admin_setting_validate ($form, $form_state){
	$limit = $form_state['values']['annotate_limit_per_node'];
		if (!is_numeric($limit)){
			form_set_error('annotate_limit_per_node',t('Plese enter a number.'));
		}
}

function annotate_admin_settings_submit($forms, $form_state){
	//����� �� ���� ������� ����� ��������, ��������� � �����.
	foreach($form_state['values']['annotate_node_types'] as $key => $value){
	// ���� ������ ���� �������� �������, ���������,
	// ������� �� � ������� ���� �������� ��������� � ��� ���� ���������,
	// � ������ ������� field_info_instance . ���� �������,
	// ����� ������� ���� ���������, �. �. ������ �������.
		if(!$value){
			$instance = field_info_instance('node','annotation',$key);
			if(!empty($instance)){
				field_delete_instance($instance);
				watchdog("Annotation","Deleted annotation field from content type: ".$key);
			} // ����� ��������, ����� ��������� ����������, � �� ���������� �������.
		}else{
		// ���� ������ ��� ���� �������� ����������, ���������, �������� �� � ������
		// ����� �������� ����. ���� ���, ������� � ��� �������� ���� ���������.
			$instance = field_info_instance('node','annotation',$key);
			if(empty($instance)){
				$instance = array(
					'field_name' => 'annotation',
					'entity_type' => 'node',
					'bundle' => $key,
					'label' => t('Annotation'),
					'widget_type' => 'text_textarea_with_summary',
					'settings' => array('display_summary' => TRUE),
					'display' => array(
						'default' => array(
							'type' => 'text_default',
						),
						'teaser' => array(
							'type' => 'text_summary_or_trimmed',
						),
					),
				);
				$instance = field_create_instance($instance);
				watchdog("Annotation","Added annotation field to content type: ".$key);
			} // ����� ��������, ����� ���� ��������� ���, � ��� �����������.
		} // ����� ��������� if.
	}// ����� ��������� foreach.
	
}









