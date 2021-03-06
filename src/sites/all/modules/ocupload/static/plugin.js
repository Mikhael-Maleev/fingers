CKEDITOR.plugins.add('OCUpload', {
  init: function(editor) {
    // Add Button
    editor.ui.addButton('OCUpload', {
      label: Drupal.t('Upload file'),
      command: 'OCUpload',
      icon: this.path + 'button.png'
    });
    // Add Command
    editor.addCommand('OCUpload', {
      exec: function(editor) {
        if (jQuery('.' + editor.id + ' .ocupload-processed').length == 0) {
          alert(Drupal.t('Module initialization error.'));
        }
      }
    });
    // Initialize module
    editor.on('dataReady', function(e) {
      if (Drupal.settings.ocupload.allowedExt == '*.;') {
        editor.getCommand('OCUpload').setState(CKEDITOR.TRISTATE_DISABLED);
        return;
      }

      jQuery('.cke_button_OCUpload:not(.ocupload-processed), .cke_button__ocupload:not(.ocupload-processed)').each(function(i) {
        var $this = jQuery(this);
        var $textarea = $this.parents('.form-item').find('textarea');
        var $editorWrapper = $textarea.next();

        var swfu = new SWFUpload({
          flash_url                : Drupal.settings.basePath + 'sites/all/libraries/swfupload/Flash/swfupload.swf',
          upload_url               : Drupal.settings.ocupload.uploadPath,
          button_placeholder_id    : $this.find('.cke_label, .cke_button_label').attr('id'),
          file_size_limit          : Drupal.settings.ocupload.sizeLimit + ' B',
          file_types               : Drupal.settings.ocupload.allowedExt,
          file_types_description   : Drupal.t('Files'),
          file_upload_limit        : 0,
          prevent_swf_caching      : false,
          button_image_url         : Drupal.settings.ocupload.modulePath + '/static/clear.gif',
          button_window_mode       : SWFUpload.WINDOW_MODE.TRANSPARENT,
          button_width             : 20,
          button_height            : 20,
          file_post_name           : 'files[file]',
          post_params              : {'phpsessid':Drupal.settings.ocupload.phpsessid},
          // After files select
          file_dialog_complete_handler: function() {
            var selection = CKEDITOR.instances[$textarea.attr('id')].getSelection();
            var selectedText = '';
            if (selection) {
              selectedText = jQuery.browser.msie && parseInt(jQuery.browser.version, 10) < 10
                ? selection.getNative().createRange().text
                : selection.getNative().toString();
            }

            swfu.addPostParam('selectedText', selectedText);
            swfu.addPostParam('formId', $textarea.closest('form').find('input[name="form_id"]').val());
            swfu.addPostParam('fieldName', $textarea.attr('name'));
            this.startUpload();
          },
          // File added in queue
          file_queued_handler: function(file) {
            var $queue = jQuery('#swfupload-queue');
            if ($queue.length == 0) {
              $queue = jQuery('<div id="swfupload-queue"></div>').appendTo('body');
            }
            $queue.prepend('<div id="queue-' + file.id + '">' + file.name + '</div>');
          },
          // Start upload one file in queue
          upload_start_handler: function(file) {
            jQuery('#queue-' + file.id).css({'background':'url(' + Drupal.settings.basePath + 'misc/progress.gif) repeat-x 0 center', 'color':'white'});
          },
          // After upload one file
          upload_success_handler: function(file, serverData) {
            jQuery('#queue-' + file.id).hide('fast', function(){
              jQuery(this).remove();
            });

            serverData = jQuery.trim(serverData);
            if (serverData.substring(0, 1) != '{') {
              return alert(Drupal.t('Server response came not in JSON format') + ': "' + serverData + '"');
            }
            response = jQuery.parseJSON(serverData);
            if (response.status) {
              var element = CKEDITOR.dom.element.createFromHtml(response.data);
              setTimeout(function(){
                CKEDITOR.instances[$textarea.attr('id')].insertElement(element);
              }, jQuery.browser.msie ? 800 : 0); // fix msie render bug
            }
            else {
              alert(response.data);
            }
          },
          // Error during upload
          upload_error_handler: function(file, errorCode, message) {
            alert('Error ' + errorCode + ': ' + message);
            jQuery('#queue-' + file.id).hide('fast', function(){
              jQuery(this).remove();
            });
          }
        });

        $this.mousedown(function(event){ event.stopPropagation(); });
        $this.addClass('ocupload-processed');
      });
    });
  }
});
