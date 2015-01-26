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
		'type' => MENU_NORMAL_ITEM, //MENU_CALLBACK,
	);
	return $items;
}


