<?php
/**
* ���������� $themeenginename_preprocessor_$hook()
* ��������������� ����� ���������� ����� �������� � ��������� ����� ������������� �������
*/
function grayscale_preprocess_breadcrumb(&$variables) {
  $variables['breadcrumb_delimiter'] = '#';
}


/**
* ��������� ����� hook_theme()
*/
function grayscale_formexample_a_nameform(&$variables){
	return $variables.'<h1>heeeeeeeeeeeeeeeeeeellllllllloooooooo</h1>';
}