<?php

/**
*@file
*Модуль для работы с системой меню Drupal.
*/

/**
* Обратный вызов страницы.
*/
function menufun_greeting($first_name ='', $last_name ='', $from_first_name ='', $from_last_name =''){
	return t('Hello @first_name @last_name from @from_first_name @from_last_name',
	array('@first_name' => $first_name, '@last_name' => $last_name,
			'@from_first_name' => $from_first_name,
			'@from_last_name' => $from_last_name));
}
/**
* Обратный вызов страницы.
*/
function menufun_farewell(){
	return t('Goodbye');
}
/**
* Обратный вызов заголовка.
*/
function menufun_title_m(){
	$now = format_date(time());
	drupal_set_title(t('It is now @time', array('@time' => $now)));
	return t('It is menu title');
}
function menufun_title_f(){
	drupal_set_title(t('It is page title'));
	$now = format_date(time());
	return t('It is menu title');
}











