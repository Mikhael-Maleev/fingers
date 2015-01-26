<?php
/*
* Пример добавления своей переменной $breadcrumb_delimiter в шаблонный файл
*/ ?>
<?php if (!empty($breadcrumb)) : ?>
	<span class="breadcrumb">
		<?php print implode(' '. $breadcrumb_delimiter .' ',$breadcrumb); ?>
		<?php print '</br>Разделитель '. $breadcrumb_delimiter; ?>
	</span>
<?php endif; ?>