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
		'page callback' => 'menufun_hello',
		'access callback' => TRUE,
		'type' => MENU_CALLBACK,
	);
	return $items;
}
/**
* Обратный вызов страницы.
*/
function menufun_hello(){
	return t('Hello!');
}

