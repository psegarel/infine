Drupal.behaviors.onePage = {
    attach: function (context, settings) {

        jQuery(".infine-sortable", context).sortable({
            placeholder: "onepage-placeholder",
            forcePlaceholderSize: true,
            forceHelperSize: true,
            start: function(e, ui){
                ui.placeholder.height(ui.item.height());
            },
            update: function (event, ui) {
                var sorts = jQuery(this).sortable('toArray');

                jQuery.ajax({
                    type: "POST",
                    url: "/admin/structure/onepage/sort",
                    data: { 'sorting': sorts }
                });
            }
        });

        jQuery(".component-action-edit", context).click(function () {
            var selector = jQuery(this).attr('href');
            jQuery(selector).parent().slideDown('fast');
        });

        jQuery(".container-action-edit", context).click(function () {
            var selector = jQuery(this).attr('href');
            jQuery(selector).parent().parent().parent().parent().slideDown('fast');
        });
    }
}
