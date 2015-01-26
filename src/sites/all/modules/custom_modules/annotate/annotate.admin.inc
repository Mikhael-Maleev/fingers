<?php

/**
*@file
*Обратные вызовы административной страници для модуля аннотирования.
*/

/**
*	Создание формы. Настройка анотирования.
*@ingroup forms
*@see system_settings_form().
*/


function annotate_admin_settings(){
	// Получение массива типов нод: ключи - это внутрение имена,
	// а значения  - "дружественные имена". Например:
	// array('page' => 'Basic page','article' => 'Articles')
	$types = node_type_get_types();
	foreach($types as $node_type){
		$options[$node_type->type] = $node_type->name;
	}
	$form['annotate_node_types'] = array(
		'#type' => 'checkboxes',
		'#title' => t('Users may annotate these content type'), // Пользователи могут аннотировать эти типы контента
		'#options' => $options,
		'#default_value' => variable_get('annotate_node_types',array('page')),
		'#description' => t('A text field will be available on this content types to make author-spesific notes.')// Для этих типов контента будут доступны текстовые поля, преданазначенные для авторских заметок
	);
	$form['annotate_deletion'] = array(
		'#type' => 'radios',
		'#title' => t('Annotations will be deleted'),//Анотации будут удалены
		'#description' => t('Select a metod for deleting annotations.'),// Выберите метод для удаления аннотаций
		'#options' => array(
			t('Never'), //Никогда
			t('Randomly'), //Случайным образом
			t('After 30 days') //Спустя 30 дней
		),
		'#default_value' => variable_get('annotate_deletion',0)//По умолчанию никогда
	);
	$form['annotate_limit_per_node'] = array(
		'#type' => 'textfield',
		'#title' => t('Annotations per node'),//Анотации в ноде
		'#description' => t('Enter the maximum number of annotations allowed per node (0 for no limit).'),// Выберите максимальное колличество аннотаций к ноде (0 не ограничено)
		'#default_value' => variable_get('annotate_limit_per_node',1),//По умолчанию никогда
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
	//Цыкло по всем флажкам типов контента, имеющимся в форме.
	foreach($form_state['values']['annotate_node_types'] as $key => $value){
	// Если флажок типа контента сброшен, проверяем,
	// имеется ли у данного типа контента связанные с ним поле аннотации,
	// с помощю функции field_info_instance . Если имеется,
	// нужно удалить поле аннотации, т. к. Флажок сброшен.
		if(!$value){
			$instance = field_info_instance('node','annotation',$key);
			if(!empty($instance)){
				field_delete_instance($instance);
				watchdog("Annotation","Deleted annotation field from content type: ".$key);
			} // Конец варианта, когда аннотация существует, и ее необходимо удалить.
		}else{
		// Если флажок для типа контента установлен, проверяем, связанно ли с данным
		// типом контента поле. Если нет, добавим в тип контента поле аннотации.
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
			} // Конец варианта, когда поля аннотации нет, и оно добавляется.
		} // Конец оператора if.
	}// Конец оператора foreach.
	
}









