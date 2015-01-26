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
		'access callback' => 'user_access',
		'access arguments' => array('recive greeting'),
		'type' => MENU_NORMAL_ITEM,
	);
	$items['menufun/farewell'] = array(
		'title' => 'Farewell',
		'page callback' => 'menufun_farewell',
		'file' => 'menufun_greeting.inc',
		'access callback' => 'user_access',
		'access arguments' => array('recive greeting'),
		'type' => MENU_NORMAL_ITEM,
	);
	return $items;
}
/**
* Реализация hook_permission()
*/
function menufun_permission(){
	return array(
		'recive greeting' => array(
			'title' => t('Recive a greeting'),
			'description' => t('Allow users recive a greeting message'),
		),
	);	
}

















