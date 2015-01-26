<?php
/**
* Реализация $themeenginename_preprocessor_$hook()
* Устанавливаемые здесь переменные будут доступны в шаблонном файле навигационной цепочки
*/
function grayscale_preprocess_breadcrumb(&$variables) {
  $variables['breadcrumb_delimiter'] = '#';
}


/**
* Темизация формы hook_theme()
*/
function grayscale_formexample_a_nameform(&$variables){
	return $variables.'<h1>heeeeeeeeeeeeeeeeeeellllllllloooooooo</h1>';
}