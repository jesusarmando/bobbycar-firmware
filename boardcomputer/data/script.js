$(document).ready(function(){
    $('form').each(function(){
        let form = $(this);
        console.log(form.attr('action'));

        form.submit(function(e){
            e.preventDefault();

            let args = {
                'data': {}
            };

            if (form.attr('method'))
                args['method']= form.attr('method');

            if (form.attr('action'))
                args['url']= form.attr('action');

            form.find('input,select').each(function(){
                let input = $(this);
                if (input.attr('name')) {
                    console.log(input.prop('nodeName'));
                    if (input.prop('nodeName') == 'INPUT' && input.attr('type') == 'checkbox') {
                        if (input.is(':checked')) {
                            args['data'][input.attr('name')] = input.attr('value') ? input.attr('value') : 'on';
                        }
                    } else {
                        args['data'][input.attr('name')] = input.val();
                    }
                } else
                    console.warn(this, 'has no name');
            });

            $.ajax(args)
                .done(function(data, textStatus, jqXHR){
                    $('#exampleModalLabel')
                        .addClass('succeeded')
                        .text('Success!');

                    $('#modalBody').text(data);
                })
                .fail(function(jqXHR, textStatus, errorThrown){
                    $('#exampleModalLabel')
                        .addClass('failed')
                        .text('Failed!');

                    $('#modalBody').text(jqXHR.responseText);

                    console.log(jqXHR);
                    console.log(textStatus);
                    console.log(errorThrown);
                })
                .always(function(){
                    $('[data-dismiss=modal],#modalFooter').show();

                });

            $('[data-dismiss=modal],#modalFooter').hide();
            $('#exampleModalLabel')
                .removeClass('failed succeeded')
                .text('Submitting data...');
            $('#modalBody').empty();
            $('#exampleModal')
                .modal({
                    'backdrop': 'static',
                    'keyboard': false,
                    'show': true
                });
        })
    })
});