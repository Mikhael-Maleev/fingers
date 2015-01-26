<?php
/**
* @file
* Это файл шаблона для визуализации formexample_a_nameform
* Здесь каждый элемент формы визуализируется индивидуально в отличии
* от визуализации формы целиком за раз, что обеспечивает высокую
* степень управления компоновкой форм. Можно также вывести форму целиком
* за раз с использованием предварительного определения компоновки в модуле
* путем вывода $variables['formexample_a_nameform_form'];
*/
print '<div id="formexample_a_nameform">';
print $variables['formexample_a_nameform']['submit'];
print $variables['formexample_a_nameform']['color'];
print $variables['formexample_a_nameform']['name'];
print $variables['formexample_a_nameform']['hidden'];
print '</div>';
 //print $variables['formexample_a_nameform_form'];