<?php

/**
*@file
*Модуль для работы с системой меню Drupal.
*/

/**
* Реализация hook_menu()
*/
function menufun_menu(){
	$items['menufun'] = array(
		'title' => 'Greeting',
		'page callback' => 'menufun_greeting',
		'file' => 'menufun_greeting.inc',
		'page arguments' => array('Michael','Maleev'),
		'access callback' => TRUE,
		'type' => MENU_CALLBACK,
	);
	return $items;
}
/**
* Обратный вызов страницы.
*/
function menufun_hello($first_name = '', $last_name = ''){
	return t('Hello @first_name @last_name from @from_first_name @from_last_name',
	array('@first_name' => $first_name, '@last_name' => $last_name));
}

