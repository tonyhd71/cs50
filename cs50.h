<!DOCTYPE html>

<html lang="en">

    <head>

        <meta charset="utf-8">
        <meta name="viewport" content="initial-scale=1, width=device-width">

        <!-- https://getbootstrap.com/ -->
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-rbsA2VBKQhggwzxH7pPCaAqO46MgnOM80zW1RWuH61DGLwZJEdK2Kadq2F9CUG65" crossorigin="anonymous">
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.2.3/dist/js/bootstrap.bundle.min.js" integrity="sha384-kenU1KFdBIe4zVF0s0G1M5b4hcpxyD9F7jL+jjXkk+Q2h455rYXK/7HAuoJl+0I4" crossorigin="anonymous"></script>

        <!-- https://jquery.com/ -->
        <script src="https://cdn.jsdelivr.net/npm/jquery@3.6.3/dist/jquery.min.js" integrity="sha256-pvPw+upLPUjgMXY0G+8O0xUf+/Im1MZjXxxgOcBQBXU=" crossorigin="anonymous"></script>

        <!-- https://fontawesome.com/ -->
        <link crossorigin="anonymous" href="https://use.fontawesome.com/releases/v5.13.0/css/all.css" integrity="sha384-Bfad6CLCknfcloXFOyFnlgtENryhrpZCe29RTifKEixXQZ38WheV+i/6YWSzkz3V" rel="stylesheet">

        <!-- https://www.ubuntu.com/ -->
        <link href="https://assets.ubuntu.com/v1/49a1a858-favicon-32x32.png" rel="icon" type="image/png">

        <link href="/static/rouge.css" rel="stylesheet">

        <script>

            

    $(function() {

        // Hide less-comfortable descriptions
        $('[data-less]').addClass('d-none');

        // Listen for checkbox
        $('#filter').on('change', function() {
            if ($('#filter').is(':checked')) {
                $('[data-less]').removeClass('d-none');
                $('[data-more]').addClass('d-none');
            }
            else {
                $('[data-more]').removeClass('d-none');
                $('[data-less]').addClass('d-none');
            }
            filter();
        }).trigger('change');

        // Listen for searches
        $('#q').on('change keyup', function() {
            filter();
        });
        $('#q').closest('form').on('submit', function(e) {
            e.preventDefault();
        });

        // Filter results
        filter();

        // Unless user's followed a link to a heading, filter index
        if (window.location.hash) {
            $('#filter').prop('checked', false).trigger('change');
        }

        // Give focus to search (after body is visible)
        else {
            $(function() {
                $('#q').focus();
            });
        }
    });

    function filter() {
        let q = $('#q').val().trim().split(/\s+/);
        if (q.length === 1 && q[0] === '') {
            q = [];
        }
        $('h1').each(function(index, element) {
            const $h1 = $(element);
            const header = $h1.val();
            const $ul = $h1.next('ul');
            $ul.children('li').each(function(index, element) {
                const $li = $(element);
                if ($('#filter').prop('checked') && $li.attr('data-filter') === undefined) {
                    $li.addClass('filtered');
                }
                else {
                    $li.removeClass('filtered');
                }
                const haystack = $h1.text() + $li.text().trim();
                let matches = q.filter(function(s) {
                    return haystack.match(new RegExp(s, 'i')) !== null;
                });
                if (matches.length === q.length) {
                    $li.removeClass('mismatched');
                }
                else {
                    $li.addClass('mismatched');
                }
            });
            if ($ul.children('li:not(.filtered, .mismatched)').length > 0) {
                $h1.removeClass('d-none');
                $ul.removeClass('d-none');
            }
            else {
                $h1.addClass('d-none');
                $ul.addClass('d-none');
            }
        });
    };



        </script>

        <script>

            $(function() {

                // Add borders to tables
                $('.table').addClass('table-bordered');

                // Enable popovers
                $('[data-bs-toggle="popover"]').each(function(index, element) {
                    new bootstrap.Popover(element, {
                        boundary: 'viewport',
                        html: true,
                        placement: 'bottom',
                        trigger: 'focus'
                    });
                });

                // Ensure all elements are styled the same
                $('h1').addClass('border-bottom fw-bold h2 mb-3 pb-2 pt-4');
                $('h2').addClass('fw-bold h3');

                // Ensure last heading can be anchored atop page
                $(window).resize(function() {
                    const top = $('h1').last().offset().top;
                    const margin = $(window).height() - ($('body').outerHeight() - top);
                    $('body').css('margin-bottom', Math.max(0, Math.ceil(margin)) + 'px');
                });
                $(window).trigger('resize');

                // Reveal body
                $('body').removeClass('invisible');
            });

        </script>

        <style>

            /* Style popovers */
            .popover {
                font-family: inherit;
                max-width: 100%;
            }

            /* Wrap long words (and URLs, whether linked or not), especially on mobile,
            but not in buttons and not in tables, which should instead scroll horizontally */
            * {
                word-break: break-word;
            }
            button, table * {
                word-break: normal;
            }

            /* Remove underlining */
            a {
                text-decoration: none;
            }
            a:hover {
                text-decoration: underline;
            }
            nav a:hover {
                text-decoration: none;
            }

            /* Match Gmail's yellow */
            a[data-bs-toggle=popover] {
                border-bottom: 2px solid rgb(252, 237, 193);
                box-shadow: inset 0 -2px 0 rgb(252, 237, 193);
                cursor: help;
            }
            a[data-bs-toggle=popover]:hover {
                background-color: rgb(252, 237, 193);
            }

            /* Match pre tags */
            code {
                color: inherit;
            }

            /* A la Jekyll theme */
            code, pre {
                background-color: #f8f9fa;
                border: 1px solid #dee2e6;
                padding: calc(.2rem - 3px) 0.2rem;
            }
            pre code {
                background-color: initial;
                border: initial;
                padding: initial;
            }

            /* Don't shrink these */
            code, pre {
                font-size: inherit;
            }

            /* Don't italicize */
            dl dt {
                font-style: normal;
            }

            /* Don't fill viewport */
            .table {
                width: inherit;
            }

        </style>

        <style>

            

    /* Don't display */
    .filtered, .mismatched {
        display: none;
    }

    /* No bullets */
    ul {
        list-style-type: none;
        padding-left: 0;
    }

    

        </style>

        <title>CS50 Manual Pages</title>

    </head>

    <body class="font-monospace invisible pb-5">

        <nav class="bg-dark navbar navbar-dark navbar-expand-xl px-4">
            <a class="navbar-brand" href="/"><i class="fas fa-list pe-3"></i>CS50 Manual Pages</a>
        </nav>

        <div class="container-fluid mt-2 px-4">
            

    <p class="mb-3 mt-4">
        Manual pages for the C standard library, the C POSIX library, and the CS50 Library for <a data-bs-content="Like you!" data-bs-toggle="popover" tabindex="0">those less comfortable</a>.
    </p>

    <form>
        <div class="mb-3">
            <input autocomplete="off" class="form-control" id="q" placeholder="Search" type="search">
        </div>
        <div class="form-check form-switch mb-4">
            <input checked class="form-check-input" id="filter" type="checkbox">
            <label class="form-check-label" for="filter">less comfortable</label>
        </div>
    </form>

    

        <h1 id="aio.h">
            <a href="#aio.h">aio.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/aio_cancel">aio_cancel</a>
                        -
                        <span data-more>cancel an outstanding asynchronous I/O request</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/aio_error">aio_error</a>
                        -
                        <span data-more>get error status of asynchronous I/O operation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/aio_fsync">aio_fsync</a>
                        -
                        <span data-more>asynchronous file synchronization</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/aio_init">aio_init</a>
                        -
                        <span data-more>asynchronous I/O initialization</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/aio_read">aio_read</a>
                        -
                        <span data-more>asynchronous read</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/aio_return">aio_return</a>
                        -
                        <span data-more>get return status of asynchronous I/O operation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/aio_suspend">aio_suspend</a>
                        -
                        <span data-more>wait for asynchronous I/O operation or timeout</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/aio_write">aio_write</a>
                        -
                        <span data-more>asynchronous write</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lio_listio">lio_listio</a>
                        -
                        <span data-more>initiate a list of I/O requests</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="arpa/inet.h">
            <a href="#arpa/inet.h">arpa/inet.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/byteorder">byteorder</a>
                        -
                        <span data-more>convert values between host and network byte order</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/htonl">htonl</a>
                        -
                        <span data-more>convert values between host and network byte order</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/htons">htons</a>
                        -
                        <span data-more>convert values between host and network byte order</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_net_ntop">inet_net_ntop</a>
                        -
                        <span data-more>Internet network number conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_net_pton">inet_net_pton</a>
                        -
                        <span data-more>Internet network number conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_ntop">inet_ntop</a>
                        -
                        <span data-more>convert IPv4 and IPv6 addresses from binary to text form</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_pton">inet_pton</a>
                        -
                        <span data-more>convert IPv4 and IPv6 addresses from text to binary form</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ntohl">ntohl</a>
                        -
                        <span data-more>convert values between host and network byte order</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ntohs">ntohs</a>
                        -
                        <span data-more>convert values between host and network byte order</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="assert.h">
            <a href="#assert.h">assert.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/assert">assert</a>
                        -
                        <span data-more>abort the program if assertion is false</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/assert_perror">assert_perror</a>
                        -
                        <span data-more>test errnum and abort</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="complex.h">
            <a href="#complex.h">complex.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/cabs">cabs</a>
                        -
                        <span data-more>absolute value of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cabsf">cabsf</a>
                        -
                        <span data-more>absolute value of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cabsl">cabsl</a>
                        -
                        <span data-more>absolute value of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cacos">cacos</a>
                        -
                        <span data-more>complex arc cosine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cacosf">cacosf</a>
                        -
                        <span data-more>complex arc cosine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cacosh">cacosh</a>
                        -
                        <span data-more>complex arc hyperbolic cosine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cacoshf">cacoshf</a>
                        -
                        <span data-more>complex arc hyperbolic cosine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cacoshl">cacoshl</a>
                        -
                        <span data-more>complex arc hyperbolic cosine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cacosl">cacosl</a>
                        -
                        <span data-more>complex arc cosine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/carg">carg</a>
                        -
                        <span data-more>calculate the complex argument</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cargf">cargf</a>
                        -
                        <span data-more>calculate the complex argument</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cargl">cargl</a>
                        -
                        <span data-more>calculate the complex argument</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/casin">casin</a>
                        -
                        <span data-more>complex arc sine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/casinf">casinf</a>
                        -
                        <span data-more>complex arc sine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/casinh">casinh</a>
                        -
                        <span data-more>complex arc sine hyperbolic</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/casinhf">casinhf</a>
                        -
                        <span data-more>complex arc sine hyperbolic</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/casinhl">casinhl</a>
                        -
                        <span data-more>complex arc sine hyperbolic</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/casinl">casinl</a>
                        -
                        <span data-more>complex arc sine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/catan">catan</a>
                        -
                        <span data-more>complex arc tangents</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/catanf">catanf</a>
                        -
                        <span data-more>complex arc tangents</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/catanh">catanh</a>
                        -
                        <span data-more>complex arc tangents hyperbolic</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/catanhf">catanhf</a>
                        -
                        <span data-more>complex arc tangents hyperbolic</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/catanhl">catanhl</a>
                        -
                        <span data-more>complex arc tangents hyperbolic</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/catanl">catanl</a>
                        -
                        <span data-more>complex arc tangents</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ccos">ccos</a>
                        -
                        <span data-more>complex cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ccosf">ccosf</a>
                        -
                        <span data-more>complex cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ccosh">ccosh</a>
                        -
                        <span data-more>complex hyperbolic cosine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ccoshf">ccoshf</a>
                        -
                        <span data-more>complex hyperbolic cosine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ccoshl">ccoshl</a>
                        -
                        <span data-more>complex hyperbolic cosine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ccosl">ccosl</a>
                        -
                        <span data-more>complex cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cexp">cexp</a>
                        -
                        <span data-more>complex exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cexp2">cexp2</a>
                        -
                        <span data-more>base-2 exponent of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cexp2f">cexp2f</a>
                        -
                        <span data-more>base-2 exponent of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cexp2l">cexp2l</a>
                        -
                        <span data-more>base-2 exponent of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cexpf">cexpf</a>
                        -
                        <span data-more>complex exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cexpl">cexpl</a>
                        -
                        <span data-more>complex exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cimag">cimag</a>
                        -
                        <span data-more>get imaginary part of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cimagf">cimagf</a>
                        -
                        <span data-more>get imaginary part of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cimagl">cimagl</a>
                        -
                        <span data-more>get imaginary part of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clog">clog</a>
                        -
                        <span data-more>natural logarithm of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clog10">clog10</a>
                        -
                        <span data-more>base-10 logarithm of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clog10f">clog10f</a>
                        -
                        <span data-more>base-10 logarithm of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clog10l">clog10l</a>
                        -
                        <span data-more>base-10 logarithm of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clog2">clog2</a>
                        -
                        <span data-more>base-2 logarithm of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clog2f">clog2f</a>
                        -
                        <span data-more>base-2 logarithm of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clog2l">clog2l</a>
                        -
                        <span data-more>base-2 logarithm of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clogf">clogf</a>
                        -
                        <span data-more>natural logarithm of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clogl">clogl</a>
                        -
                        <span data-more>natural logarithm of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/complex">complex</a>
                        -
                        <span data-more>basics of complex mathematics</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/conj">conj</a>
                        -
                        <span data-more>calculate the complex conjugate</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/conjf">conjf</a>
                        -
                        <span data-more>calculate the complex conjugate</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/conjl">conjl</a>
                        -
                        <span data-more>calculate the complex conjugate</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cpow">cpow</a>
                        -
                        <span data-more>complex power function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cpowf">cpowf</a>
                        -
                        <span data-more>complex power function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cpowl">cpowl</a>
                        -
                        <span data-more>complex power function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cproj">cproj</a>
                        -
                        <span data-more>project into Riemann Sphere</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cprojf">cprojf</a>
                        -
                        <span data-more>project into Riemann Sphere</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cprojl">cprojl</a>
                        -
                        <span data-more>project into Riemann Sphere</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/creal">creal</a>
                        -
                        <span data-more>get real part of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/crealf">crealf</a>
                        -
                        <span data-more>get real part of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/creall">creall</a>
                        -
                        <span data-more>get real part of a complex number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/csin">csin</a>
                        -
                        <span data-more>complex sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/csinf">csinf</a>
                        -
                        <span data-more>complex sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/csinh">csinh</a>
                        -
                        <span data-more>complex hyperbolic sine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/csinhf">csinhf</a>
                        -
                        <span data-more>complex hyperbolic sine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/csinhl">csinhl</a>
                        -
                        <span data-more>complex hyperbolic sine</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/csinl">csinl</a>
                        -
                        <span data-more>complex sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/csqrt">csqrt</a>
                        -
                        <span data-more>complex square root</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/csqrtf">csqrtf</a>
                        -
                        <span data-more>complex square root</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/csqrtl">csqrtl</a>
                        -
                        <span data-more>complex square root</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ctan">ctan</a>
                        -
                        <span data-more>complex tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ctanf">ctanf</a>
                        -
                        <span data-more>complex tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ctanh">ctanh</a>
                        -
                        <span data-more>complex hyperbolic tangent</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ctanhf">ctanhf</a>
                        -
                        <span data-more>complex hyperbolic tangent</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ctanhl">ctanhl</a>
                        -
                        <span data-more>complex hyperbolic tangent</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ctanl">ctanl</a>
                        -
                        <span data-more>complex tangent function</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="cs50.h">
            <a href="#cs50.h">cs50.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li data-filter>
                        <a href="3/get_char">get_char</a>
                        -
                        <span data-more>prompts user for a line of text from stdin and returns...</span>
                        <span data-less>prompt a user for a <code class="language-plaintext highlighter-rouge">char</code></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/get_double">get_double</a>
                        -
                        <span data-more>prompts user for a line of text from stdin and returns...</span>
                        <span data-less>prompt a user for a <code class="language-plaintext highlighter-rouge">double</code></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/get_float">get_float</a>
                        -
                        <span data-more>prompts user for a line of text from stdin and returns...</span>
                        <span data-less>prompt a user for a <code class="language-plaintext highlighter-rouge">float</code></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/get_int">get_int</a>
                        -
                        <span data-more>prompts user for a line of text from stdin and returns...</span>
                        <span data-less>prompt a user for an <code class="language-plaintext highlighter-rouge">int</code></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/get_long">get_long</a>
                        -
                        <span data-more>prompts user for a line of text from stdin and returns...</span>
                        <span data-less>prompt a user for an <code class="language-plaintext highlighter-rouge">long</code></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/get_long_long">get_long_long</a>
                        -
                        <span data-more>prompts user for a line of text from stdin and returns...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/get_string">get_string</a>
                        -
                        <span data-more>prompts user for a line of text from stdin and returns...</span>
                        <span data-less>prompt a user for a <code class="language-plaintext highlighter-rouge">string</code></span>
                    </li>

                

            

        </ul>

    

        <h1 id="ctype.h">
            <a href="#ctype.h">ctype.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li data-filter>
                        <a href="3/isalnum">isalnum</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less>check whether a character is alphanumeric</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isalnum_l">isalnum_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/isalpha">isalpha</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less>check whether a character is alphabetical</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isalpha_l">isalpha_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isascii">isascii</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isascii_l">isascii_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/isblank">isblank</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less>check whether a character is blank (i.e., a space or tab)</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isblank_l">isblank_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iscntrl">iscntrl</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iscntrl_l">iscntrl_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/isdigit">isdigit</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less>check whether a character is a digit</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isdigit_l">isdigit_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isgraph">isgraph</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isgraph_l">isgraph_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/islower">islower</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less>check whether a character is lowercase</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/islower_l">islower_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isprint">isprint</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isprint_l">isprint_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/ispunct">ispunct</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less>check whether a character is punctuation</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ispunct_l">ispunct_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/isspace">isspace</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less>check whether a character is whitespace (e.g., a newline, space, or tab)</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isspace_l">isspace_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/isupper">isupper</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less>check whether a character is uppercase</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isupper_l">isupper_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isxdigit">isxdigit</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isxdigit_l">isxdigit_l</a>
                        -
                        <span data-more>character classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/toascii">toascii</a>
                        -
                        <span data-more>convert character to ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/tolower">tolower</a>
                        -
                        <span data-more>convert uppercase or lowercase</span>
                        <span data-less>convert a <code class="language-plaintext highlighter-rouge">char</code> to lowercase</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tolower_l">tolower_l</a>
                        -
                        <span data-more>convert uppercase or lowercase</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/toupper">toupper</a>
                        -
                        <span data-more>convert uppercase or lowercase</span>
                        <span data-less>convert a <code class="language-plaintext highlighter-rouge">char</code> to uppercase</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/toupper_l">toupper_l</a>
                        -
                        <span data-more>convert uppercase or lowercase</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="dirent.h">
            <a href="#dirent.h">dirent.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/alphasort">alphasort</a>
                        -
                        <span data-more>scan a directory for matching entries</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getdirentries">getdirentries</a>
                        -
                        <span data-more>get directory entries in a filesystem-independent format</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/readdir">readdir</a>
                        -
                        <span data-more>read a directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/readdir_r">readdir_r</a>
                        -
                        <span data-more>read a directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scandir">scandir</a>
                        -
                        <span data-more>scan a directory for matching entries</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scandirat">scandirat</a>
                        -
                        <span data-more>scan a directory for matching entries</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/seekdir">seekdir</a>
                        -
                        <span data-more>set the position of the next readdir() call in the dir...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/telldir">telldir</a>
                        -
                        <span data-more>return current location in directory stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/versionsort">versionsort</a>
                        -
                        <span data-more>scan a directory for matching entries</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="dlfcn.h">
            <a href="#dlfcn.h">dlfcn.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/dladdr">dladdr</a>
                        -
                        <span data-more>translate address to symbolic information</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dladdr1">dladdr1</a>
                        -
                        <span data-more>translate address to symbolic information</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dlclose">dlclose</a>
                        -
                        <span data-more>open and close a shared object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dlerror">dlerror</a>
                        -
                        <span data-more>obtain error diagnostic for functions in the dlopen API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dlmopen">dlmopen</a>
                        -
                        <span data-more>open and close a shared object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dlopen">dlopen</a>
                        -
                        <span data-more>open and close a shared object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dlsym">dlsym</a>
                        -
                        <span data-more>obtain address of a symbol in a shared object or execu...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dlvsym">dlvsym</a>
                        -
                        <span data-more>obtain address of a symbol in a shared object or execu...</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="errno.h">
            <a href="#errno.h">errno.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/errno">errno</a>
                        -
                        <span data-more>number of last error</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/program_invocation_name">program_invocation_name</a>
                        -
                        <span data-more>obtain name used to invoke calling program</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/program_invocation_short_name">program_invocation_short_name</a>
                        -
                        <span data-more>obtain name used to invoke calling program</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="fcntl.h">
            <a href="#fcntl.h">fcntl.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/arm_fadvise">arm_fadvise</a>
                        -
                        <span data-more>predeclare an access pattern for file data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/arm_fadvise64_64">arm_fadvise64_64</a>
                        -
                        <span data-more>predeclare an access pattern for file data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/arm_sync_file_range">arm_sync_file_range</a>
                        -
                        <span data-more>sync a file segment with disk</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fadvise64">fadvise64</a>
                        -
                        <span data-more>predeclare an access pattern for file data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fadvise64_64">fadvise64_64</a>
                        -
                        <span data-more>predeclare an access pattern for file data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fallocate">fallocate</a>
                        -
                        <span data-more>manipulate file space</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fanotify_init">fanotify_init</a>
                        -
                        <span data-more>create and initialize fanotify group</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/futimens">futimens</a>
                        -
                        <span data-more>change file timestamps with nanosecond precision</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/futimesat">futimesat</a>
                        -
                        <span data-more>change timestamps of a file relative to a directory fi...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/posix_fadvise">posix_fadvise</a>
                        -
                        <span data-more>predeclare an access pattern for file data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/posix_fallocate">posix_fallocate</a>
                        -
                        <span data-more>allocate file space</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/readahead">readahead</a>
                        -
                        <span data-more>initiate file readahead into page cache</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/splice">splice</a>
                        -
                        <span data-more>splice data to/from a pipe</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sync_file_range">sync_file_range</a>
                        -
                        <span data-more>sync a file segment with disk</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sync_file_range2">sync_file_range2</a>
                        -
                        <span data-more>sync a file segment with disk</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/tee">tee</a>
                        -
                        <span data-more>duplicating pipe content</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/utimensat">utimensat</a>
                        -
                        <span data-more>change file timestamps with nanosecond precision</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/vmsplice">vmsplice</a>
                        -
                        <span data-more>splice user pages to/from a pipe</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="fenv.h">
            <a href="#fenv.h">fenv.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/feclearexcept">feclearexcept</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fedisableexcept">fedisableexcept</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/feenableexcept">feenableexcept</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fegetenv">fegetenv</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fegetexcept">fegetexcept</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fegetexceptflag">fegetexceptflag</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fegetround">fegetround</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/feholdexcept">feholdexcept</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fenv">fenv</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/feraiseexcept">feraiseexcept</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fesetenv">fesetenv</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fesetexceptflag">fesetexceptflag</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fesetround">fesetround</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fetestexcept">fetestexcept</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/feupdateenv">feupdateenv</a>
                        -
                        <span data-more>floating-point rounding and exception handling</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="fmtmsg.h">
            <a href="#fmtmsg.h">fmtmsg.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/addseverity">addseverity</a>
                        -
                        <span data-more>introduce new severity classes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmtmsg">fmtmsg</a>
                        -
                        <span data-more>print formatted error messages</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="fnmatch.h">
            <a href="#fnmatch.h">fnmatch.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/fnmatch">fnmatch</a>
                        -
                        <span data-more>match filename or pathname</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="ftw.h">
            <a href="#ftw.h">ftw.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/ftw">ftw</a>
                        -
                        <span data-more>file tree walk</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nftw">nftw</a>
                        -
                        <span data-more>file tree walk</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="glob.h">
            <a href="#glob.h">glob.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/glob">glob</a>
                        -
                        <span data-more>find pathnames matching a pattern, free memory from gl...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/globfree">globfree</a>
                        -
                        <span data-more>find pathnames matching a pattern, free memory from gl...</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="grp.h">
            <a href="#grp.h">grp.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/fgetgrent_r">fgetgrent_r</a>
                        -
                        <span data-more>get group file entry reentrantly</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getgrent_r">getgrent_r</a>
                        -
                        <span data-more>get group file entry reentrantly</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getgrouplist">getgrouplist</a>
                        -
                        <span data-more>get list of groups to which a user belongs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putgrent">putgrent</a>
                        -
                        <span data-more>write a group database entry to a file</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="iconv.h">
            <a href="#iconv.h">iconv.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/iconv">iconv</a>
                        -
                        <span data-more>perform character set conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iconv_close">iconv_close</a>
                        -
                        <span data-more>deallocate descriptor for character set conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iconv_open">iconv_open</a>
                        -
                        <span data-more>allocate descriptor for character set conversion</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="inttypes.h">
            <a href="#inttypes.h">inttypes.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/strtoimax">strtoimax</a>
                        -
                        <span data-more>convert string to integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtoumax">strtoumax</a>
                        -
                        <span data-more>convert string to integer</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="langinfo.h">
            <a href="#langinfo.h">langinfo.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/nl_langinfo">nl_langinfo</a>
                        -
                        <span data-more>query language and locale information</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nl_langinfo_l">nl_langinfo_l</a>
                        -
                        <span data-more>query language and locale information</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="libgen.h">
            <a href="#libgen.h">libgen.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/basename">basename</a>
                        -
                        <span data-more>parse pathname components</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dirname">dirname</a>
                        -
                        <span data-more>parse pathname components</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="limits.h">
            <a href="#limits.h">limits.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/MB_LEN_MAX">MB_LEN_MAX</a>
                        -
                        <span data-more>maximum multibyte length of a character across all loc...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/realpath">realpath</a>
                        -
                        <span data-more>return the canonicalized absolute pathname</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="locale.h">
            <a href="#locale.h">locale.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/duplocale">duplocale</a>
                        -
                        <span data-more>duplicate a locale object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/freelocale">freelocale</a>
                        -
                        <span data-more>create, modify, and free a locale object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/locale">locale</a>
                        -
                        <span data-more>description of multilanguage support</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/localeconv">localeconv</a>
                        -
                        <span data-more>get numeric formatting information</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/newlocale">newlocale</a>
                        -
                        <span data-more>create, modify, and free a locale object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setlocale">setlocale</a>
                        -
                        <span data-more>set the current locale</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/uselocale">uselocale</a>
                        -
                        <span data-more>set/get the locale for the calling thread</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="math.h">
            <a href="#math.h">math.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/acos">acos</a>
                        -
                        <span data-more>arc cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/acosf">acosf</a>
                        -
                        <span data-more>arc cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/acosh">acosh</a>
                        -
                        <span data-more>inverse hyperbolic cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/acoshf">acoshf</a>
                        -
                        <span data-more>inverse hyperbolic cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/acoshl">acoshl</a>
                        -
                        <span data-more>inverse hyperbolic cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/acosl">acosl</a>
                        -
                        <span data-more>arc cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/asin">asin</a>
                        -
                        <span data-more>arc sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/asinf">asinf</a>
                        -
                        <span data-more>arc sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/asinh">asinh</a>
                        -
                        <span data-more>inverse hyperbolic sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/asinhf">asinhf</a>
                        -
                        <span data-more>inverse hyperbolic sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/asinhl">asinhl</a>
                        -
                        <span data-more>inverse hyperbolic sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/asinl">asinl</a>
                        -
                        <span data-more>arc sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atan">atan</a>
                        -
                        <span data-more>arc tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atan2">atan2</a>
                        -
                        <span data-more>arc tangent function of two variables</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atan2f">atan2f</a>
                        -
                        <span data-more>arc tangent function of two variables</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atan2l">atan2l</a>
                        -
                        <span data-more>arc tangent function of two variables</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atanf">atanf</a>
                        -
                        <span data-more>arc tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atanh">atanh</a>
                        -
                        <span data-more>inverse hyperbolic tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atanhf">atanhf</a>
                        -
                        <span data-more>inverse hyperbolic tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atanhl">atanhl</a>
                        -
                        <span data-more>inverse hyperbolic tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atanl">atanl</a>
                        -
                        <span data-more>arc tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cbrt">cbrt</a>
                        -
                        <span data-more>cube root function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cbrtf">cbrtf</a>
                        -
                        <span data-more>cube root function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cbrtl">cbrtl</a>
                        -
                        <span data-more>cube root function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/ceil">ceil</a>
                        -
                        <span data-more>ceiling function: smallest integral value not less tha...</span>
                        <span data-less>calculate the ceiling of a number</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ceilf">ceilf</a>
                        -
                        <span data-more>ceiling function: smallest integral value not less tha...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ceill">ceill</a>
                        -
                        <span data-more>ceiling function: smallest integral value not less tha...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/copysign">copysign</a>
                        -
                        <span data-more>copy sign of a number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/copysignf">copysignf</a>
                        -
                        <span data-more>copy sign of a number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/copysignl">copysignl</a>
                        -
                        <span data-more>copy sign of a number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cos">cos</a>
                        -
                        <span data-more>cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cosf">cosf</a>
                        -
                        <span data-more>cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cosh">cosh</a>
                        -
                        <span data-more>hyperbolic cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/coshf">coshf</a>
                        -
                        <span data-more>hyperbolic cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/coshl">coshl</a>
                        -
                        <span data-more>hyperbolic cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cosl">cosl</a>
                        -
                        <span data-more>cosine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/drem">drem</a>
                        -
                        <span data-more>floating-point remainder function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dremf">dremf</a>
                        -
                        <span data-more>floating-point remainder function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dreml">dreml</a>
                        -
                        <span data-more>floating-point remainder function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/erf">erf</a>
                        -
                        <span data-more>error function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/erfc">erfc</a>
                        -
                        <span data-more>complementary error function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/erfcf">erfcf</a>
                        -
                        <span data-more>complementary error function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/erfcl">erfcl</a>
                        -
                        <span data-more>complementary error function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/erff">erff</a>
                        -
                        <span data-more>error function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/erfl">erfl</a>
                        -
                        <span data-more>error function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/exp">exp</a>
                        -
                        <span data-more>base-e exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/exp10">exp10</a>
                        -
                        <span data-more>base-10 exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/exp10f">exp10f</a>
                        -
                        <span data-more>base-10 exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/exp10l">exp10l</a>
                        -
                        <span data-more>base-10 exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/exp2">exp2</a>
                        -
                        <span data-more>base-2 exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/exp2f">exp2f</a>
                        -
                        <span data-more>base-2 exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/exp2l">exp2l</a>
                        -
                        <span data-more>base-2 exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/expf">expf</a>
                        -
                        <span data-more>base-e exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/expl">expl</a>
                        -
                        <span data-more>base-e exponential function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/expm1">expm1</a>
                        -
                        <span data-more>exponential minus 1</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/expm1f">expm1f</a>
                        -
                        <span data-more>exponential minus 1</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/expm1l">expm1l</a>
                        -
                        <span data-more>exponential minus 1</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fabs">fabs</a>
                        -
                        <span data-more>absolute value of floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fabsf">fabsf</a>
                        -
                        <span data-more>absolute value of floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fabsl">fabsl</a>
                        -
                        <span data-more>absolute value of floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fdim">fdim</a>
                        -
                        <span data-more>positive difference</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fdimf">fdimf</a>
                        -
                        <span data-more>positive difference</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fdiml">fdiml</a>
                        -
                        <span data-more>positive difference</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/finite">finite</a>
                        -
                        <span data-more>BSD floating-point classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/finitef">finitef</a>
                        -
                        <span data-more>BSD floating-point classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/finitel">finitel</a>
                        -
                        <span data-more>BSD floating-point classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/floor">floor</a>
                        -
                        <span data-more>largest integral value not greater than argument</span>
                        <span data-less>calculate the floor of a number</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/floorf">floorf</a>
                        -
                        <span data-more>largest integral value not greater than argument</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/floorl">floorl</a>
                        -
                        <span data-more>largest integral value not greater than argument</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fma">fma</a>
                        -
                        <span data-more>floating-point multiply and add</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmaf">fmaf</a>
                        -
                        <span data-more>floating-point multiply and add</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmal">fmal</a>
                        -
                        <span data-more>floating-point multiply and add</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmax">fmax</a>
                        -
                        <span data-more>determine maximum of two floating-point numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmaxf">fmaxf</a>
                        -
                        <span data-more>determine maximum of two floating-point numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmaxl">fmaxl</a>
                        -
                        <span data-more>determine maximum of two floating-point numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmin">fmin</a>
                        -
                        <span data-more>determine minimum of two floating-point numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fminf">fminf</a>
                        -
                        <span data-more>determine minimum of two floating-point numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fminl">fminl</a>
                        -
                        <span data-more>determine minimum of two floating-point numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmod">fmod</a>
                        -
                        <span data-more>floating-point remainder function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmodf">fmodf</a>
                        -
                        <span data-more>floating-point remainder function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmodl">fmodl</a>
                        -
                        <span data-more>floating-point remainder function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fpclassify">fpclassify</a>
                        -
                        <span data-more>floating-point classification macros</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/frexp">frexp</a>
                        -
                        <span data-more>convert floating-point number to fractional and integr...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/frexpf">frexpf</a>
                        -
                        <span data-more>convert floating-point number to fractional and integr...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/frexpl">frexpl</a>
                        -
                        <span data-more>convert floating-point number to fractional and integr...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gamma">gamma</a>
                        -
                        <span data-more>(logarithm of the) gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gammaf">gammaf</a>
                        -
                        <span data-more>(logarithm of the) gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gammal">gammal</a>
                        -
                        <span data-more>(logarithm of the) gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/HUGE_VAL">HUGE_VAL</a>
                        -
                        <span data-more>floating-point constants</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/HUGE_VALF">HUGE_VALF</a>
                        -
                        <span data-more>floating-point constants</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/HUGE_VALL">HUGE_VALL</a>
                        -
                        <span data-more>floating-point constants</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hypot">hypot</a>
                        -
                        <span data-more>Euclidean distance function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hypotf">hypotf</a>
                        -
                        <span data-more>Euclidean distance function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hypotl">hypotl</a>
                        -
                        <span data-more>Euclidean distance function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ilogb">ilogb</a>
                        -
                        <span data-more>get integer exponent of a floating-point value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ilogbf">ilogbf</a>
                        -
                        <span data-more>get integer exponent of a floating-point value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ilogbl">ilogbl</a>
                        -
                        <span data-more>get integer exponent of a floating-point value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/INFINITY">INFINITY</a>
                        -
                        <span data-more>floating-point constants</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isfinite">isfinite</a>
                        -
                        <span data-more>floating-point classification macros</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isgreater">isgreater</a>
                        -
                        <span data-more>floating-point relational tests without exception for NaN</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isgreaterequal">isgreaterequal</a>
                        -
                        <span data-more>floating-point relational tests without exception for NaN</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isinf">isinf</a>
                        -
                        <span data-more>floating-point classification macros</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isinff">isinff</a>
                        -
                        <span data-more>BSD floating-point classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isinfl">isinfl</a>
                        -
                        <span data-more>BSD floating-point classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isless">isless</a>
                        -
                        <span data-more>floating-point relational tests without exception for NaN</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/islessequal">islessequal</a>
                        -
                        <span data-more>floating-point relational tests without exception for NaN</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/islessgreater">islessgreater</a>
                        -
                        <span data-more>floating-point relational tests without exception for NaN</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isnan">isnan</a>
                        -
                        <span data-more>floating-point classification macros</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isnanf">isnanf</a>
                        -
                        <span data-more>BSD floating-point classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isnanl">isnanl</a>
                        -
                        <span data-more>BSD floating-point classification functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isnormal">isnormal</a>
                        -
                        <span data-more>floating-point classification macros</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isunordered">isunordered</a>
                        -
                        <span data-more>floating-point relational tests without exception for NaN</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/j0">j0</a>
                        -
                        <span data-more>Bessel functions of the first kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/j0f">j0f</a>
                        -
                        <span data-more>Bessel functions of the first kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/j0l">j0l</a>
                        -
                        <span data-more>Bessel functions of the first kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/j1">j1</a>
                        -
                        <span data-more>Bessel functions of the first kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/j1f">j1f</a>
                        -
                        <span data-more>Bessel functions of the first kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/j1l">j1l</a>
                        -
                        <span data-more>Bessel functions of the first kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/jn">jn</a>
                        -
                        <span data-more>Bessel functions of the first kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/jnf">jnf</a>
                        -
                        <span data-more>Bessel functions of the first kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/jnl">jnl</a>
                        -
                        <span data-more>Bessel functions of the first kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ldexp">ldexp</a>
                        -
                        <span data-more>multiply floating-point number by integral power of 2</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ldexpf">ldexpf</a>
                        -
                        <span data-more>multiply floating-point number by integral power of 2</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ldexpl">ldexpl</a>
                        -
                        <span data-more>multiply floating-point number by integral power of 2</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lgamma">lgamma</a>
                        -
                        <span data-more>log gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lgamma_r">lgamma_r</a>
                        -
                        <span data-more>log gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lgammaf">lgammaf</a>
                        -
                        <span data-more>log gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lgammaf_r">lgammaf_r</a>
                        -
                        <span data-more>log gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lgammal">lgammal</a>
                        -
                        <span data-more>log gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lgammal_r">lgammal_r</a>
                        -
                        <span data-more>log gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/llrint">llrint</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/llrintf">llrintf</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/llrintl">llrintl</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/llround">llround</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/llroundf">llroundf</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/llroundl">llroundl</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/log">log</a>
                        -
                        <span data-more>natural logarithmic function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/log10">log10</a>
                        -
                        <span data-more>base-10 logarithmic function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/log10f">log10f</a>
                        -
                        <span data-more>base-10 logarithmic function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/log10l">log10l</a>
                        -
                        <span data-more>base-10 logarithmic function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/log1p">log1p</a>
                        -
                        <span data-more>logarithm of 1 plus argument</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/log1pf">log1pf</a>
                        -
                        <span data-more>logarithm of 1 plus argument</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/log1pl">log1pl</a>
                        -
                        <span data-more>logarithm of 1 plus argument</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/log2">log2</a>
                        -
                        <span data-more>base-2 logarithmic function</span>
                        <span data-less>calculate the base-2 logarithm of a number</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/log2f">log2f</a>
                        -
                        <span data-more>base-2 logarithmic function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/log2l">log2l</a>
                        -
                        <span data-more>base-2 logarithmic function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/logb">logb</a>
                        -
                        <span data-more>get exponent of a floating-point value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/logbf">logbf</a>
                        -
                        <span data-more>get exponent of a floating-point value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/logbl">logbl</a>
                        -
                        <span data-more>get exponent of a floating-point value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/logf">logf</a>
                        -
                        <span data-more>natural logarithmic function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/logl">logl</a>
                        -
                        <span data-more>natural logarithmic function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lrint">lrint</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lrintf">lrintf</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lrintl">lrintl</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lround">lround</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lroundf">lroundf</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lroundl">lroundl</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/math_error">math_error</a>
                        -
                        <span data-more>detecting errors from mathematical functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/matherr">matherr</a>
                        -
                        <span data-more>SVID math library exception handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/modf">modf</a>
                        -
                        <span data-more>extract signed integral and fractional values from flo...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/modff">modff</a>
                        -
                        <span data-more>extract signed integral and fractional values from flo...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/modfl">modfl</a>
                        -
                        <span data-more>extract signed integral and fractional values from flo...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/NAN">NAN</a>
                        -
                        <span data-more>floating-point constants</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nan">nan</a>
                        -
                        <span data-more>return &#39;Not a Number&#39;</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nanf">nanf</a>
                        -
                        <span data-more>return &#39;Not a Number&#39;</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nanl">nanl</a>
                        -
                        <span data-more>return &#39;Not a Number&#39;</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nearbyint">nearbyint</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nearbyintf">nearbyintf</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nearbyintl">nearbyintl</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nextafter">nextafter</a>
                        -
                        <span data-more>floating-point number manipulation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nextafterf">nextafterf</a>
                        -
                        <span data-more>floating-point number manipulation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nextafterl">nextafterl</a>
                        -
                        <span data-more>floating-point number manipulation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nextdown">nextdown</a>
                        -
                        <span data-more>return next floating-point number toward positive/nega...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nextdownf">nextdownf</a>
                        -
                        <span data-more>return next floating-point number toward positive/nega...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nextdownl">nextdownl</a>
                        -
                        <span data-more>return next floating-point number toward positive/nega...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nexttoward">nexttoward</a>
                        -
                        <span data-more>floating-point number manipulation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nexttowardf">nexttowardf</a>
                        -
                        <span data-more>floating-point number manipulation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nexttowardl">nexttowardl</a>
                        -
                        <span data-more>floating-point number manipulation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nextup">nextup</a>
                        -
                        <span data-more>return next floating-point number toward positive/nega...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nextupf">nextupf</a>
                        -
                        <span data-more>return next floating-point number toward positive/nega...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nextupl">nextupl</a>
                        -
                        <span data-more>return next floating-point number toward positive/nega...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/pow">pow</a>
                        -
                        <span data-more>power functions</span>
                        <span data-less>raise a number to a power</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pow10">pow10</a>
                        -
                        <span data-more>base-10 power functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pow10f">pow10f</a>
                        -
                        <span data-more>base-10 power functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pow10l">pow10l</a>
                        -
                        <span data-more>base-10 power functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/powf">powf</a>
                        -
                        <span data-more>power functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/powl">powl</a>
                        -
                        <span data-more>power functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/remainder">remainder</a>
                        -
                        <span data-more>floating-point remainder function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/remainderf">remainderf</a>
                        -
                        <span data-more>floating-point remainder function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/remainderl">remainderl</a>
                        -
                        <span data-more>floating-point remainder function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/remquo">remquo</a>
                        -
                        <span data-more>remainder and part of quotient</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/remquof">remquof</a>
                        -
                        <span data-more>remainder and part of quotient</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/remquol">remquol</a>
                        -
                        <span data-more>remainder and part of quotient</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rint">rint</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rintf">rintf</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rintl">rintl</a>
                        -
                        <span data-more>round to nearest integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/round">round</a>
                        -
                        <span data-more>round to nearest integer, away from zero</span>
                        <span data-less>round a number to the nearest integer</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/roundf">roundf</a>
                        -
                        <span data-more>round to nearest integer, away from zero</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/roundl">roundl</a>
                        -
                        <span data-more>round to nearest integer, away from zero</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scalb">scalb</a>
                        -
                        <span data-more>multiply floating-point number by integral power of ra...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scalbf">scalbf</a>
                        -
                        <span data-more>multiply floating-point number by integral power of ra...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scalbl">scalbl</a>
                        -
                        <span data-more>multiply floating-point number by integral power of ra...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scalbln">scalbln</a>
                        -
                        <span data-more>multiply floating-point number by integral power of radix</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scalblnf">scalblnf</a>
                        -
                        <span data-more>multiply floating-point number by integral power of radix</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scalblnl">scalblnl</a>
                        -
                        <span data-more>multiply floating-point number by integral power of radix</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scalbn">scalbn</a>
                        -
                        <span data-more>multiply floating-point number by integral power of radix</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scalbnf">scalbnf</a>
                        -
                        <span data-more>multiply floating-point number by integral power of radix</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/scalbnl">scalbnl</a>
                        -
                        <span data-more>multiply floating-point number by integral power of radix</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/signbit">signbit</a>
                        -
                        <span data-more>test sign of a real floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/signgam">signgam</a>
                        -
                        <span data-more>log gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/significand">significand</a>
                        -
                        <span data-more>get mantissa of floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/significandf">significandf</a>
                        -
                        <span data-more>get mantissa of floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/significandl">significandl</a>
                        -
                        <span data-more>get mantissa of floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sin">sin</a>
                        -
                        <span data-more>sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sincos">sincos</a>
                        -
                        <span data-more>calculate sin and cos simultaneously</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sincosf">sincosf</a>
                        -
                        <span data-more>calculate sin and cos simultaneously</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sincosl">sincosl</a>
                        -
                        <span data-more>calculate sin and cos simultaneously</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sinf">sinf</a>
                        -
                        <span data-more>sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sinh">sinh</a>
                        -
                        <span data-more>hyperbolic sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sinhf">sinhf</a>
                        -
                        <span data-more>hyperbolic sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sinhl">sinhl</a>
                        -
                        <span data-more>hyperbolic sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sinl">sinl</a>
                        -
                        <span data-more>sine function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/sqrt">sqrt</a>
                        -
                        <span data-more>square root function</span>
                        <span data-less>calculate the square root of a number</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sqrtf">sqrtf</a>
                        -
                        <span data-more>square root function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sqrtl">sqrtl</a>
                        -
                        <span data-more>square root function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tan">tan</a>
                        -
                        <span data-more>tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tanf">tanf</a>
                        -
                        <span data-more>tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tanh">tanh</a>
                        -
                        <span data-more>hyperbolic tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tanhf">tanhf</a>
                        -
                        <span data-more>hyperbolic tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tanhl">tanhl</a>
                        -
                        <span data-more>hyperbolic tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tanl">tanl</a>
                        -
                        <span data-more>tangent function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tgamma">tgamma</a>
                        -
                        <span data-more>true gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tgammaf">tgammaf</a>
                        -
                        <span data-more>true gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tgammal">tgammal</a>
                        -
                        <span data-more>true gamma function</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/trunc">trunc</a>
                        -
                        <span data-more>round to integer, toward zero</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/truncf">truncf</a>
                        -
                        <span data-more>round to integer, toward zero</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/truncl">truncl</a>
                        -
                        <span data-more>round to integer, toward zero</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/y0">y0</a>
                        -
                        <span data-more>Bessel functions of the second kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/y0f">y0f</a>
                        -
                        <span data-more>Bessel functions of the second kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/y0l">y0l</a>
                        -
                        <span data-more>Bessel functions of the second kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/y1">y1</a>
                        -
                        <span data-more>Bessel functions of the second kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/y1f">y1f</a>
                        -
                        <span data-more>Bessel functions of the second kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/y1l">y1l</a>
                        -
                        <span data-more>Bessel functions of the second kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/yn">yn</a>
                        -
                        <span data-more>Bessel functions of the second kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ynf">ynf</a>
                        -
                        <span data-more>Bessel functions of the second kind</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ynl">ynl</a>
                        -
                        <span data-more>Bessel functions of the second kind</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="monetary.h">
            <a href="#monetary.h">monetary.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/strfmon">strfmon</a>
                        -
                        <span data-more>convert monetary value to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strfmon_l">strfmon_l</a>
                        -
                        <span data-more>convert monetary value to a string</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="mqueue.h">
            <a href="#mqueue.h">mqueue.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/mq_close">mq_close</a>
                        -
                        <span data-more>close a message queue descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mq_getattr">mq_getattr</a>
                        -
                        <span data-more>get/set message queue attributes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mq_notify">mq_notify</a>
                        -
                        <span data-more>register for notification when a message is available</span>
                        <span data-less></span>
                    </li>

                

                    

                    <li>
                        <a href="3/mq_notify">mq_notify</a>
                        -
                        <span data-more>register for notification when a message is available</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mq_open">mq_open</a>
                        -
                        <span data-more>open a message queue</span>
                        <span data-less></span>
                    </li>

                

                    

                    <li>
                        <a href="3/mq_open">mq_open</a>
                        -
                        <span data-more>open a message queue</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mq_receive">mq_receive</a>
                        -
                        <span data-more>receive a message from a message queue</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mq_send">mq_send</a>
                        -
                        <span data-more>send a message to a message queue</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mq_setattr">mq_setattr</a>
                        -
                        <span data-more>get/set message queue attributes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mq_timedreceive">mq_timedreceive</a>
                        -
                        <span data-more>receive a message from a message queue</span>
                        <span data-less></span>
                    </li>

                

                    

                    <li>
                        <a href="3/mq_timedreceive">mq_timedreceive</a>
                        -
                        <span data-more>receive a message from a message queue</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mq_timedsend">mq_timedsend</a>
                        -
                        <span data-more>send a message to a message queue</span>
                        <span data-less></span>
                    </li>

                

                    

                    <li>
                        <a href="3/mq_timedsend">mq_timedsend</a>
                        -
                        <span data-more>send a message to a message queue</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mq_unlink">mq_unlink</a>
                        -
                        <span data-more>remove a message queue</span>
                        <span data-less></span>
                    </li>

                

                    

                    <li>
                        <a href="3/mq_unlink">mq_unlink</a>
                        -
                        <span data-more>remove a message queue</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="net/if.h">
            <a href="#net/if.h">net/if.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/if_freenameindex">if_freenameindex</a>
                        -
                        <span data-more>get network interface names and indexes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/if_indextoname">if_indextoname</a>
                        -
                        <span data-more>mappings between network interface names and indexes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/if_nameindex">if_nameindex</a>
                        -
                        <span data-more>get network interface names and indexes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/if_nametoindex">if_nametoindex</a>
                        -
                        <span data-more>mappings between network interface names and indexes</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="netdb.h">
            <a href="#netdb.h">netdb.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/endhostent">endhostent</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/endnetent">endnetent</a>
                        -
                        <span data-more>get network entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/endnetgrent">endnetgrent</a>
                        -
                        <span data-more>handle network group entries</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/endprotoent">endprotoent</a>
                        -
                        <span data-more>get protocol entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/endrpcent">endrpcent</a>
                        -
                        <span data-more>get RPC entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/endservent">endservent</a>
                        -
                        <span data-more>get service entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gai_cancel">gai_cancel</a>
                        -
                        <span data-more>asynchronous network address and service translation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gai_error">gai_error</a>
                        -
                        <span data-more>asynchronous network address and service translation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gai_suspend">gai_suspend</a>
                        -
                        <span data-more>asynchronous network address and service translation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getaddrinfo_a">getaddrinfo_a</a>
                        -
                        <span data-more>asynchronous network address and service translation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gethostbyaddr">gethostbyaddr</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gethostbyaddr_r">gethostbyaddr_r</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gethostbyname">gethostbyname</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gethostbyname2">gethostbyname2</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gethostbyname2_r">gethostbyname2_r</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gethostbyname_r">gethostbyname_r</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gethostent">gethostent</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gethostent_r">gethostent_r</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getnetbyaddr">getnetbyaddr</a>
                        -
                        <span data-more>get network entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getnetbyaddr_r">getnetbyaddr_r</a>
                        -
                        <span data-more>get network entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getnetbyname">getnetbyname</a>
                        -
                        <span data-more>get network entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getnetbyname_r">getnetbyname_r</a>
                        -
                        <span data-more>get network entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getnetent">getnetent</a>
                        -
                        <span data-more>get network entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getnetent_r">getnetent_r</a>
                        -
                        <span data-more>get network entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getnetgrent">getnetgrent</a>
                        -
                        <span data-more>handle network group entries</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getnetgrent_r">getnetgrent_r</a>
                        -
                        <span data-more>handle network group entries</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getprotobyname">getprotobyname</a>
                        -
                        <span data-more>get protocol entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getprotobyname_r">getprotobyname_r</a>
                        -
                        <span data-more>get protocol entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getprotobynumber">getprotobynumber</a>
                        -
                        <span data-more>get protocol entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getprotobynumber_r">getprotobynumber_r</a>
                        -
                        <span data-more>get protocol entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getprotoent">getprotoent</a>
                        -
                        <span data-more>get protocol entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getprotoent_r">getprotoent_r</a>
                        -
                        <span data-more>get protocol entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getrpcbyname">getrpcbyname</a>
                        -
                        <span data-more>get RPC entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getrpcbyname_r">getrpcbyname_r</a>
                        -
                        <span data-more>get RPC entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getrpcbynumber">getrpcbynumber</a>
                        -
                        <span data-more>get RPC entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getrpcbynumber_r">getrpcbynumber_r</a>
                        -
                        <span data-more>get RPC entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getrpcent">getrpcent</a>
                        -
                        <span data-more>get RPC entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getrpcent_r">getrpcent_r</a>
                        -
                        <span data-more>get RPC entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getservbyname">getservbyname</a>
                        -
                        <span data-more>get service entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getservbyname_r">getservbyname_r</a>
                        -
                        <span data-more>get service entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getservbyport">getservbyport</a>
                        -
                        <span data-more>get service entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getservbyport_r">getservbyport_r</a>
                        -
                        <span data-more>get service entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getservent">getservent</a>
                        -
                        <span data-more>get service entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getservent_r">getservent_r</a>
                        -
                        <span data-more>get service entry (reentrant)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/h_errno">h_errno</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/herror">herror</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hstrerror">hstrerror</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/innetgr">innetgr</a>
                        -
                        <span data-more>handle network group entries</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iruserok">iruserok</a>
                        -
                        <span data-more>routines for returning a stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iruserok_af">iruserok_af</a>
                        -
                        <span data-more>routines for returning a stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rcmd">rcmd</a>
                        -
                        <span data-more>routines for returning a stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rcmd_af">rcmd_af</a>
                        -
                        <span data-more>routines for returning a stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rexec">rexec</a>
                        -
                        <span data-more>return stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rexec_af">rexec_af</a>
                        -
                        <span data-more>return stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rresvport">rresvport</a>
                        -
                        <span data-more>routines for returning a stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rresvport_af">rresvport_af</a>
                        -
                        <span data-more>routines for returning a stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ruserok">ruserok</a>
                        -
                        <span data-more>routines for returning a stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ruserok_af">ruserok_af</a>
                        -
                        <span data-more>routines for returning a stream to a remote command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sethostent">sethostent</a>
                        -
                        <span data-more>get network host entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setnetent">setnetent</a>
                        -
                        <span data-more>get network entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setnetgrent">setnetgrent</a>
                        -
                        <span data-more>handle network group entries</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setprotoent">setprotoent</a>
                        -
                        <span data-more>get protocol entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setrpcent">setrpcent</a>
                        -
                        <span data-more>get RPC entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setservent">setservent</a>
                        -
                        <span data-more>get service entry</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="netinet/in.h">
            <a href="#netinet/in.h">netinet/in.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/dn_comp">dn_comp</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dn_expand">dn_expand</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_init">res_init</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_mkquery">res_mkquery</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_nclose">res_nclose</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_ninit">res_ninit</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_nmkquery">res_nmkquery</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_nquery">res_nquery</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_nquerydomain">res_nquerydomain</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_nsearch">res_nsearch</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_nsend">res_nsend</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_query">res_query</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_querydomain">res_querydomain</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_search">res_search</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/res_send">res_send</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/resolver">resolver</a>
                        -
                        <span data-more>resolver routines</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="nl_types.h">
            <a href="#nl_types.h">nl_types.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/catclose">catclose</a>
                        -
                        <span data-more>open/close a message catalog</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/catgets">catgets</a>
                        -
                        <span data-more>get message from a message catalog</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/catopen">catopen</a>
                        -
                        <span data-more>open/close a message catalog</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="poll.h">
            <a href="#poll.h">poll.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/poll">poll</a>
                        -
                        <span data-more>wait for some event on a file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/ppoll">ppoll</a>
                        -
                        <span data-more>wait for some event on a file descriptor</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="pthread.h">
            <a href="#pthread.h">pthread.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_destroy">pthread_attr_destroy</a>
                        -
                        <span data-more>initialize and destroy thread attributes object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getaffinity_np">pthread_attr_getaffinity_np</a>
                        -
                        <span data-more>set/get CPU affinity attribute in thread at...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getdetachstate">pthread_attr_getdetachstate</a>
                        -
                        <span data-more>set/get detach state attribute in thread at...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getguardsize">pthread_attr_getguardsize</a>
                        -
                        <span data-more>set/get guard size attribute in thread attrib...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getinheritsched">pthread_attr_getinheritsched</a>
                        -
                        <span data-more>set/get inherit-scheduler attribute in thr...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getschedparam">pthread_attr_getschedparam</a>
                        -
                        <span data-more>set/get scheduling parameter attributes in t...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getschedpolicy">pthread_attr_getschedpolicy</a>
                        -
                        <span data-more>set/get scheduling policy attribute in thre...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getscope">pthread_attr_getscope</a>
                        -
                        <span data-more>set/get contention scope attribute in thread attr...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getsigmask_np">pthread_attr_getsigmask_np</a>
                        -
                        <span data-more>set/get signal mask attribute in thread attr...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getstack">pthread_attr_getstack</a>
                        -
                        <span data-more>set/get stack attributes in thread attributes object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getstackaddr">pthread_attr_getstackaddr</a>
                        -
                        <span data-more>set/get stack address attribute in thread att...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_getstacksize">pthread_attr_getstacksize</a>
                        -
                        <span data-more>set/get stack size attribute in thread attrib...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_init">pthread_attr_init</a>
                        -
                        <span data-more>initialize and destroy thread attributes object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setaffinity_np">pthread_attr_setaffinity_np</a>
                        -
                        <span data-more>set/get CPU affinity attribute in thread at...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setdetachstate">pthread_attr_setdetachstate</a>
                        -
                        <span data-more>set/get detach state attribute in thread at...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setguardsize">pthread_attr_setguardsize</a>
                        -
                        <span data-more>set/get guard size attribute in thread attrib...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setinheritsched">pthread_attr_setinheritsched</a>
                        -
                        <span data-more>set/get inherit-scheduler attribute in thr...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setschedparam">pthread_attr_setschedparam</a>
                        -
                        <span data-more>set/get scheduling parameter attributes in t...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setschedpolicy">pthread_attr_setschedpolicy</a>
                        -
                        <span data-more>set/get scheduling policy attribute in thre...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setscope">pthread_attr_setscope</a>
                        -
                        <span data-more>set/get contention scope attribute in thread attr...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setsigmask_np">pthread_attr_setsigmask_np</a>
                        -
                        <span data-more>set/get signal mask attribute in thread attr...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setstack">pthread_attr_setstack</a>
                        -
                        <span data-more>set/get stack attributes in thread attributes object</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setstackaddr">pthread_attr_setstackaddr</a>
                        -
                        <span data-more>set/get stack address attribute in thread att...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_attr_setstacksize">pthread_attr_setstacksize</a>
                        -
                        <span data-more>set/get stack size attribute in thread attrib...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_cancel">pthread_cancel</a>
                        -
                        <span data-more>send a cancellation request to a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_cleanup_pop">pthread_cleanup_pop</a>
                        -
                        <span data-more>push and pop thread cancellation clean-up handlers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_cleanup_pop_restore_np">pthread_cleanup_pop_restore_np</a>
                        -
                        <span data-more>push and pop thread cancellation clean-u...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_cleanup_push">pthread_cleanup_push</a>
                        -
                        <span data-more>push and pop thread cancellation clean-up handlers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_cleanup_push_defer_np">pthread_cleanup_push_defer_np</a>
                        -
                        <span data-more>push and pop thread cancellation clean-up...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_create">pthread_create</a>
                        -
                        <span data-more>create a new thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_detach">pthread_detach</a>
                        -
                        <span data-more>detach a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_equal">pthread_equal</a>
                        -
                        <span data-more>compare thread IDs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_exit">pthread_exit</a>
                        -
                        <span data-more>terminate calling thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_getaffinity_np">pthread_getaffinity_np</a>
                        -
                        <span data-more>set/get CPU affinity of a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_getattr_default_np">pthread_getattr_default_np</a>
                        -
                        <span data-more>get or set default thread-creation attributes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_getattr_np">pthread_getattr_np</a>
                        -
                        <span data-more>get attributes of created thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_getconcurrency">pthread_getconcurrency</a>
                        -
                        <span data-more>set/get the concurrency level</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_getcpuclockid">pthread_getcpuclockid</a>
                        -
                        <span data-more>retrieve ID of a thread&#39;s CPU time clock</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_getname_np">pthread_getname_np</a>
                        -
                        <span data-more>set/get the name of a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_getschedparam">pthread_getschedparam</a>
                        -
                        <span data-more>set/get scheduling policy and parameters of a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_join">pthread_join</a>
                        -
                        <span data-more>join with a terminated thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_kill_other_threads_np">pthread_kill_other_threads_np</a>
                        -
                        <span data-more>terminate all other threads in process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_mutex_consistent">pthread_mutex_consistent</a>
                        -
                        <span data-more>make a robust mutex consistent</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_mutex_consistent_np">pthread_mutex_consistent_np</a>
                        -
                        <span data-more>make a robust mutex consistent</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_mutexattr_getpshared">pthread_mutexattr_getpshared</a>
                        -
                        <span data-more>get/set process-shared mutex attribute</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_mutexattr_getrobust">pthread_mutexattr_getrobust</a>
                        -
                        <span data-more>get and set the robustness attribute of a m...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_mutexattr_getrobust_np">pthread_mutexattr_getrobust_np</a>
                        -
                        <span data-more>get and set the robustness attribute of ...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_mutexattr_setpshared">pthread_mutexattr_setpshared</a>
                        -
                        <span data-more>get/set process-shared mutex attribute</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_mutexattr_setrobust">pthread_mutexattr_setrobust</a>
                        -
                        <span data-more>get and set the robustness attribute of a m...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_mutexattr_setrobust_np">pthread_mutexattr_setrobust_np</a>
                        -
                        <span data-more>get and set the robustness attribute of ...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_rwlockattr_getkind_np">pthread_rwlockattr_getkind_np</a>
                        -
                        <span data-more>set/get the read-write lock kind of the t...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_rwlockattr_setkind_np">pthread_rwlockattr_setkind_np</a>
                        -
                        <span data-more>set/get the read-write lock kind of the t...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_self">pthread_self</a>
                        -
                        <span data-more>obtain ID of the calling thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_setaffinity_np">pthread_setaffinity_np</a>
                        -
                        <span data-more>set/get CPU affinity of a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_setattr_default_np">pthread_setattr_default_np</a>
                        -
                        <span data-more>get or set default thread-creation attributes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_setcancelstate">pthread_setcancelstate</a>
                        -
                        <span data-more>set cancelability state and type</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_setcanceltype">pthread_setcanceltype</a>
                        -
                        <span data-more>set cancelability state and type</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_setconcurrency">pthread_setconcurrency</a>
                        -
                        <span data-more>set/get the concurrency level</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_setname_np">pthread_setname_np</a>
                        -
                        <span data-more>set/get the name of a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_setschedparam">pthread_setschedparam</a>
                        -
                        <span data-more>set/get scheduling policy and parameters of a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_setschedprio">pthread_setschedprio</a>
                        -
                        <span data-more>set scheduling priority of a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_spin_destroy">pthread_spin_destroy</a>
                        -
                        <span data-more>initialize or destroy a spin lock</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_spin_init">pthread_spin_init</a>
                        -
                        <span data-more>initialize or destroy a spin lock</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_spin_lock">pthread_spin_lock</a>
                        -
                        <span data-more>lock and unlock a spin lock</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_spin_trylock">pthread_spin_trylock</a>
                        -
                        <span data-more>lock and unlock a spin lock</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_spin_unlock">pthread_spin_unlock</a>
                        -
                        <span data-more>lock and unlock a spin lock</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_testcancel">pthread_testcancel</a>
                        -
                        <span data-more>request delivery of any pending cancellation request</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_timedjoin_np">pthread_timedjoin_np</a>
                        -
                        <span data-more>try to join with a terminated thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_tryjoin_np">pthread_tryjoin_np</a>
                        -
                        <span data-more>try to join with a terminated thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_yield">pthread_yield</a>
                        -
                        <span data-more>yield the processor</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="pwd.h">
            <a href="#pwd.h">pwd.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/fgetpwent_r">fgetpwent_r</a>
                        -
                        <span data-more>get passwd file entry reentrantly</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getpwent_r">getpwent_r</a>
                        -
                        <span data-more>get passwd file entry reentrantly</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="regex.h">
            <a href="#regex.h">regex.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/regcomp">regcomp</a>
                        -
                        <span data-more>POSIX regex functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/regerror">regerror</a>
                        -
                        <span data-more>POSIX regex functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/regex">regex</a>
                        -
                        <span data-more>POSIX regex functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/regexec">regexec</a>
                        -
                        <span data-more>POSIX regex functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/regfree">regfree</a>
                        -
                        <span data-more>POSIX regex functions</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sched.h">
            <a href="#sched.h">sched.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/__clone2">__clone2</a>
                        -
                        <span data-more>create a child process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/clone">clone</a>
                        -
                        <span data-more>create a child process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/clone2">clone2</a>
                        -
                        <span data-more>create a child process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/clone3">clone3</a>
                        -
                        <span data-more>create a child process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_ALLOC">CPU_ALLOC</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_ALLOC_SIZE">CPU_ALLOC_SIZE</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_AND">CPU_AND</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_AND_S">CPU_AND_S</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_CLR">CPU_CLR</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_CLR_S">CPU_CLR_S</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_COUNT">CPU_COUNT</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_COUNT_S">CPU_COUNT_S</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_EQUAL">CPU_EQUAL</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_EQUAL_S">CPU_EQUAL_S</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_FREE">CPU_FREE</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_ISSET">CPU_ISSET</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_ISSET_S">CPU_ISSET_S</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_OR">CPU_OR</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_OR_S">CPU_OR_S</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_SET">CPU_SET</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_SET_S">CPU_SET_S</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_XOR">CPU_XOR</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_XOR_S">CPU_XOR_S</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_ZERO">CPU_ZERO</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CPU_ZERO_S">CPU_ZERO_S</a>
                        -
                        <span data-more>macros for manipulating CPU sets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_get_priority_max">sched_get_priority_max</a>
                        -
                        <span data-more>get static priority range</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_get_priority_min">sched_get_priority_min</a>
                        -
                        <span data-more>get static priority range</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_getaffinity">sched_getaffinity</a>
                        -
                        <span data-more>set and get a thread&#39;s CPU affinity mask</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_getattr">sched_getattr</a>
                        -
                        <span data-more>set and get scheduling policy and attributes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sched_getcpu">sched_getcpu</a>
                        -
                        <span data-more>determine CPU on which the calling thread is running</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_getparam">sched_getparam</a>
                        -
                        <span data-more>set and get scheduling parameters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_getscheduler">sched_getscheduler</a>
                        -
                        <span data-more>set and get scheduling policy/parameters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_rr_get_interval">sched_rr_get_interval</a>
                        -
                        <span data-more>get the SCHED_RR interval for the named process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_setaffinity">sched_setaffinity</a>
                        -
                        <span data-more>set and get a thread&#39;s CPU affinity mask</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_setattr">sched_setattr</a>
                        -
                        <span data-more>set and get scheduling policy and attributes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_setparam">sched_setparam</a>
                        -
                        <span data-more>set and get scheduling parameters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_setscheduler">sched_setscheduler</a>
                        -
                        <span data-more>set and get scheduling policy/parameters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sched_yield">sched_yield</a>
                        -
                        <span data-more>yield the processor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setns">setns</a>
                        -
                        <span data-more>reassociate thread with a namespace</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/unshare">unshare</a>
                        -
                        <span data-more>disassociate parts of the process execution context</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="search.h">
            <a href="#search.h">search.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/hcreate">hcreate</a>
                        -
                        <span data-more>hash table management</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hcreate_r">hcreate_r</a>
                        -
                        <span data-more>hash table management</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hdestroy">hdestroy</a>
                        -
                        <span data-more>hash table management</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hdestroy_r">hdestroy_r</a>
                        -
                        <span data-more>hash table management</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hsearch">hsearch</a>
                        -
                        <span data-more>hash table management</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hsearch_r">hsearch_r</a>
                        -
                        <span data-more>hash table management</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/insque">insque</a>
                        -
                        <span data-more>insert/remove an item from a queue</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lfind">lfind</a>
                        -
                        <span data-more>linear search of an array</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lsearch">lsearch</a>
                        -
                        <span data-more>linear search of an array</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/remque">remque</a>
                        -
                        <span data-more>insert/remove an item from a queue</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tdelete">tdelete</a>
                        -
                        <span data-more>manage a binary search tree</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tdestroy">tdestroy</a>
                        -
                        <span data-more>manage a binary search tree</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tfind">tfind</a>
                        -
                        <span data-more>manage a binary search tree</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tsearch">tsearch</a>
                        -
                        <span data-more>manage a binary search tree</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/twalk">twalk</a>
                        -
                        <span data-more>manage a binary search tree</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/twalk_r">twalk_r</a>
                        -
                        <span data-more>manage a binary search tree</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="semaphore.h">
            <a href="#semaphore.h">semaphore.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/sem_close">sem_close</a>
                        -
                        <span data-more>close a named semaphore</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sem_destroy">sem_destroy</a>
                        -
                        <span data-more>destroy an unnamed semaphore</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sem_getvalue">sem_getvalue</a>
                        -
                        <span data-more>get the value of a semaphore</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sem_init">sem_init</a>
                        -
                        <span data-more>initialize an unnamed semaphore</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sem_open">sem_open</a>
                        -
                        <span data-more>initialize and open a named semaphore</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sem_post">sem_post</a>
                        -
                        <span data-more>unlock a semaphore</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sem_timedwait">sem_timedwait</a>
                        -
                        <span data-more>lock a semaphore</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sem_trywait">sem_trywait</a>
                        -
                        <span data-more>lock a semaphore</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sem_unlink">sem_unlink</a>
                        -
                        <span data-more>remove a named semaphore</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sem_wait">sem_wait</a>
                        -
                        <span data-more>lock a semaphore</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="setjmp.h">
            <a href="#setjmp.h">setjmp.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/longjmp">longjmp</a>
                        -
                        <span data-more>performing a nonlocal goto</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setjmp">setjmp</a>
                        -
                        <span data-more>performing a nonlocal goto</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/siglongjmp">siglongjmp</a>
                        -
                        <span data-more>performing a nonlocal goto</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigsetjmp">sigsetjmp</a>
                        -
                        <span data-more>performing a nonlocal goto</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="signal.h">
            <a href="#signal.h">signal.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/bsd_signal">bsd_signal</a>
                        -
                        <span data-more>signal handling with BSD semantics</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gsignal">gsignal</a>
                        -
                        <span data-more>software signal facility</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/killpg">killpg</a>
                        -
                        <span data-more>send signal to a process group</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pidfd_send_signal">pidfd_send_signal</a>
                        -
                        <span data-more>send a signal to a process specified by a file descri...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/psiginfo">psiginfo</a>
                        -
                        <span data-more>print signal description</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/psignal">psignal</a>
                        -
                        <span data-more>print signal description</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_kill">pthread_kill</a>
                        -
                        <span data-more>send a signal to a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_sigmask">pthread_sigmask</a>
                        -
                        <span data-more>examine and change mask of blocked signals</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pthread_sigqueue">pthread_sigqueue</a>
                        -
                        <span data-more>queue a signal and data to a thread</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/raise">raise</a>
                        -
                        <span data-more>send a signal to the caller</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/rt_sigaction">rt_sigaction</a>
                        -
                        <span data-more>examine and change a signal action</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/rt_sigpending">rt_sigpending</a>
                        -
                        <span data-more>examine pending signals</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/rt_sigprocmask">rt_sigprocmask</a>
                        -
                        <span data-more>examine and change blocked signals</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/rt_sigsuspend">rt_sigsuspend</a>
                        -
                        <span data-more>wait for a signal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/rt_sigtimedwait">rt_sigtimedwait</a>
                        -
                        <span data-more>synchronously wait for queued signals</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sigaction">sigaction</a>
                        -
                        <span data-more>examine and change a signal action</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigaddset">sigaddset</a>
                        -
                        <span data-more>POSIX signal set operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sigaltstack">sigaltstack</a>
                        -
                        <span data-more>set and/or get signal stack context</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigandset">sigandset</a>
                        -
                        <span data-more>POSIX signal set operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigblock">sigblock</a>
                        -
                        <span data-more>BSD signal API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigdelset">sigdelset</a>
                        -
                        <span data-more>POSIX signal set operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigemptyset">sigemptyset</a>
                        -
                        <span data-more>POSIX signal set operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigfillset">sigfillset</a>
                        -
                        <span data-more>POSIX signal set operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/siggetmask">siggetmask</a>
                        -
                        <span data-more>BSD signal API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sighold">sighold</a>
                        -
                        <span data-more>System V signal API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigignore">sigignore</a>
                        -
                        <span data-more>System V signal API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/siginterrupt">siginterrupt</a>
                        -
                        <span data-more>allow signals to interrupt system calls</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigisemptyset">sigisemptyset</a>
                        -
                        <span data-more>POSIX signal set operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigismember">sigismember</a>
                        -
                        <span data-more>POSIX signal set operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigmask">sigmask</a>
                        -
                        <span data-more>BSD signal API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/signal">signal</a>
                        -
                        <span data-more>ANSI C signal handling</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigorset">sigorset</a>
                        -
                        <span data-more>POSIX signal set operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigpause">sigpause</a>
                        -
                        <span data-more>atomically release blocked signals and wait for interrupt</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sigpending">sigpending</a>
                        -
                        <span data-more>examine pending signals</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sigprocmask">sigprocmask</a>
                        -
                        <span data-more>examine and change blocked signals</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigqueue">sigqueue</a>
                        -
                        <span data-more>queue a signal and data to a process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigrelse">sigrelse</a>
                        -
                        <span data-more>System V signal API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigset">sigset</a>
                        -
                        <span data-more>System V signal API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigsetmask">sigsetmask</a>
                        -
                        <span data-more>BSD signal API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigsetops">sigsetops</a>
                        -
                        <span data-more>POSIX signal set operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigstack">sigstack</a>
                        -
                        <span data-more>set and/or get signal stack context</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sigsuspend">sigsuspend</a>
                        -
                        <span data-more>wait for a signal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sigtimedwait">sigtimedwait</a>
                        -
                        <span data-more>synchronously wait for queued signals</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigvec">sigvec</a>
                        -
                        <span data-more>BSD signal API</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigwait">sigwait</a>
                        -
                        <span data-more>wait for a signal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sigwaitinfo">sigwaitinfo</a>
                        -
                        <span data-more>synchronously wait for queued signals</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ssignal">ssignal</a>
                        -
                        <span data-more>software signal facility</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sysv_signal">sysv_signal</a>
                        -
                        <span data-more>signal handling with System V semantics</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/timer_create">timer_create</a>
                        -
                        <span data-more>create a POSIX per-process timer</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="spawn.h">
            <a href="#spawn.h">spawn.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/posix_spawn">posix_spawn</a>
                        -
                        <span data-more>spawn a process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/posix_spawnp">posix_spawnp</a>
                        -
                        <span data-more>spawn a process</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="stdarg.h">
            <a href="#stdarg.h">stdarg.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/stdarg">stdarg</a>
                        -
                        <span data-more>variable argument lists</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/va_arg">va_arg</a>
                        -
                        <span data-more>variable argument lists</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/va_copy">va_copy</a>
                        -
                        <span data-more>variable argument lists</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/va_end">va_end</a>
                        -
                        <span data-more>variable argument lists</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/va_start">va_start</a>
                        -
                        <span data-more>variable argument lists</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="stddef.h">
            <a href="#stddef.h">stddef.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/offsetof">offsetof</a>
                        -
                        <span data-more>offset of a structure member</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcstoimax">wcstoimax</a>
                        -
                        <span data-more>convert wide-character string to integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcstoumax">wcstoumax</a>
                        -
                        <span data-more>convert wide-character string to integer</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="stdio.h">
            <a href="#stdio.h">stdio.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/__fbufsize">__fbufsize</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/__flbf">__flbf</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/__fpending">__fpending</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/__fpurge">__fpurge</a>
                        -
                        <span data-more>purge a stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/__freadable">__freadable</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/__freading">__freading</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/__fsetlocking">__fsetlocking</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/__fwritable">__fwritable</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/__fwriting">__fwriting</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/_flushlbf">_flushlbf</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/addmntent">addmntent</a>
                        -
                        <span data-more>get filesystem descriptor file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/asprintf">asprintf</a>
                        -
                        <span data-more>print to allocated string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clearerr">clearerr</a>
                        -
                        <span data-more>check and reset stream status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clearerr_unlocked">clearerr_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ctermid">ctermid</a>
                        -
                        <span data-more>get controlling terminal name</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dprintf">dprintf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/endmntent">endmntent</a>
                        -
                        <span data-more>get filesystem descriptor file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/fclose">fclose</a>
                        -
                        <span data-more>close a stream</span>
                        <span data-less>close a file</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fcloseall">fcloseall</a>
                        -
                        <span data-more>close all open streams</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fdopen">fdopen</a>
                        -
                        <span data-more>stream open functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/feof">feof</a>
                        -
                        <span data-more>check and reset stream status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/feof_unlocked">feof_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ferror">ferror</a>
                        -
                        <span data-more>check and reset stream status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ferror_unlocked">ferror_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fflush">fflush</a>
                        -
                        <span data-more>flush a stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fflush_unlocked">fflush_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgetc">fgetc</a>
                        -
                        <span data-more>input of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgetc_unlocked">fgetc_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgetgrent">fgetgrent</a>
                        -
                        <span data-more>get group file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgetpos">fgetpos</a>
                        -
                        <span data-more>reposition a stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgetpwent">fgetpwent</a>
                        -
                        <span data-more>get password file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgets">fgets</a>
                        -
                        <span data-more>input of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgets_unlocked">fgets_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgetwc">fgetwc</a>
                        -
                        <span data-more>read a wide character from a FILE stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgetwc_unlocked">fgetwc_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgetws_unlocked">fgetws_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fileno">fileno</a>
                        -
                        <span data-more>check and reset stream status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fileno_unlocked">fileno_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/flockfile">flockfile</a>
                        -
                        <span data-more>lock FILE for stdio</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fmemopen">fmemopen</a>
                        -
                        <span data-more>open memory as stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/fopen">fopen</a>
                        -
                        <span data-more>stream open functions</span>
                        <span data-less>open a file</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fopencookie">fopencookie</a>
                        -
                        <span data-more>opening a custom stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/fprintf">fprintf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less>print to a file</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fpurge">fpurge</a>
                        -
                        <span data-more>purge a stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fputc">fputc</a>
                        -
                        <span data-more>output of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fputc_unlocked">fputc_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fputs">fputs</a>
                        -
                        <span data-more>output of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fputs_unlocked">fputs_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fputwc">fputwc</a>
                        -
                        <span data-more>write a wide character to a FILE stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fputwc_unlocked">fputwc_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fputws_unlocked">fputws_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/fread">fread</a>
                        -
                        <span data-more>binary stream input/output</span>
                        <span data-less>read bytes from a file</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fread_unlocked">fread_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/freopen">freopen</a>
                        -
                        <span data-more>stream open functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/fscanf">fscanf</a>
                        -
                        <span data-more>input format conversion</span>
                        <span data-less>get input from a file</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fseek">fseek</a>
                        -
                        <span data-more>reposition a stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fseeko">fseeko</a>
                        -
                        <span data-more>seek to or report file position</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fsetpos">fsetpos</a>
                        -
                        <span data-more>reposition a stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ftell">ftell</a>
                        -
                        <span data-more>reposition a stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ftello">ftello</a>
                        -
                        <span data-more>seek to or report file position</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ftrylockfile">ftrylockfile</a>
                        -
                        <span data-more>lock FILE for stdio</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/funlockfile">funlockfile</a>
                        -
                        <span data-more>lock FILE for stdio</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fwprintf">fwprintf</a>
                        -
                        <span data-more>formatted wide-character output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/fwrite">fwrite</a>
                        -
                        <span data-more>binary stream input/output</span>
                        <span data-less>write bytes to a file</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fwrite_unlocked">fwrite_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getc">getc</a>
                        -
                        <span data-more>input of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getc_unlocked">getc_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getchar">getchar</a>
                        -
                        <span data-more>input of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getchar_unlocked">getchar_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getdelim">getdelim</a>
                        -
                        <span data-more>delimited string input</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getline">getline</a>
                        -
                        <span data-more>delimited string input</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getmntent">getmntent</a>
                        -
                        <span data-more>get filesystem descriptor file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getmntent_r">getmntent_r</a>
                        -
                        <span data-more>get filesystem descriptor file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gets">gets</a>
                        -
                        <span data-more>get a string from standard input (DEPRECATED)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getw">getw</a>
                        -
                        <span data-more>input and output of words (ints)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getwc">getwc</a>
                        -
                        <span data-more>read a wide character from a FILE stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getwc_unlocked">getwc_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getwchar_unlocked">getwchar_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/hasmntopt">hasmntopt</a>
                        -
                        <span data-more>get filesystem descriptor file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/open_memstream">open_memstream</a>
                        -
                        <span data-more>open a dynamic memory buffer stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/open_wmemstream">open_wmemstream</a>
                        -
                        <span data-more>open a dynamic memory buffer stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pclose">pclose</a>
                        -
                        <span data-more>pipe stream to or from a process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/perror">perror</a>
                        -
                        <span data-more>print a system error message</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/popen">popen</a>
                        -
                        <span data-more>pipe stream to or from a process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/printf">printf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less>print to the screen</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putc">putc</a>
                        -
                        <span data-more>output of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putc_unlocked">putc_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putchar">putchar</a>
                        -
                        <span data-more>output of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putchar_unlocked">putchar_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putpwent">putpwent</a>
                        -
                        <span data-more>write a password file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/puts">puts</a>
                        -
                        <span data-more>output of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putw">putw</a>
                        -
                        <span data-more>input and output of words (ints)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putwc">putwc</a>
                        -
                        <span data-more>write a wide character to a FILE stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putwc_unlocked">putwc_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putwchar_unlocked">putwchar_unlocked</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/remove">remove</a>
                        -
                        <span data-more>remove a file or directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/rename">rename</a>
                        -
                        <span data-more>change the name or location of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/renameat">renameat</a>
                        -
                        <span data-more>change the name or location of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/renameat2">renameat2</a>
                        -
                        <span data-more>change the name or location of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rewind">rewind</a>
                        -
                        <span data-more>reposition a stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/scanf">scanf</a>
                        -
                        <span data-more>input format conversion</span>
                        <span data-less>get input from a user</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setbuf">setbuf</a>
                        -
                        <span data-more>stream buffering operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setbuffer">setbuffer</a>
                        -
                        <span data-more>stream buffering operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setlinebuf">setlinebuf</a>
                        -
                        <span data-more>stream buffering operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setmntent">setmntent</a>
                        -
                        <span data-more>get filesystem descriptor file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setvbuf">setvbuf</a>
                        -
                        <span data-more>stream buffering operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/snprintf">snprintf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/sprintf">sprintf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less>print to a string</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sscanf">sscanf</a>
                        -
                        <span data-more>input format conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/stderr">stderr</a>
                        -
                        <span data-more>standard I/O streams</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/stdin">stdin</a>
                        -
                        <span data-more>standard I/O streams</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/stdio">stdio</a>
                        -
                        <span data-more>standard input/output library functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/stdio_ext">stdio_ext</a>
                        -
                        <span data-more>interfaces to stdio FILE structure</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/stdout">stdout</a>
                        -
                        <span data-more>standard I/O streams</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/swprintf">swprintf</a>
                        -
                        <span data-more>formatted wide-character output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sys_errlist">sys_errlist</a>
                        -
                        <span data-more>print a system error message</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sys_nerr">sys_nerr</a>
                        -
                        <span data-more>print a system error message</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tempnam">tempnam</a>
                        -
                        <span data-more>create a name for a temporary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tmpfile">tmpfile</a>
                        -
                        <span data-more>create a temporary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tmpnam">tmpnam</a>
                        -
                        <span data-more>create a name for a temporary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tmpnam_r">tmpnam_r</a>
                        -
                        <span data-more>create a name for a temporary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ungetc">ungetc</a>
                        -
                        <span data-more>input of characters and strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/unlocked_stdio">unlocked_stdio</a>
                        -
                        <span data-more>nonlocking stdio functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vasprintf">vasprintf</a>
                        -
                        <span data-more>print to allocated string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vdprintf">vdprintf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vfprintf">vfprintf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vfscanf">vfscanf</a>
                        -
                        <span data-more>input format conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vfwprintf">vfwprintf</a>
                        -
                        <span data-more>formatted wide-character output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vprintf">vprintf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vscanf">vscanf</a>
                        -
                        <span data-more>input format conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vsnprintf">vsnprintf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vsprintf">vsprintf</a>
                        -
                        <span data-more>formatted output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vsscanf">vsscanf</a>
                        -
                        <span data-more>input format conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vswprintf">vswprintf</a>
                        -
                        <span data-more>formatted wide-character output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vwprintf">vwprintf</a>
                        -
                        <span data-more>formatted wide-character output conversion</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wprintf">wprintf</a>
                        -
                        <span data-more>formatted wide-character output conversion</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="stdlib.h">
            <a href="#stdlib.h">stdlib.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/a64l">a64l</a>
                        -
                        <span data-more>convert between long and base-64</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/abort">abort</a>
                        -
                        <span data-more>cause abnormal process termination</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/abs">abs</a>
                        -
                        <span data-more>compute the absolute value of an integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/aligned_alloc">aligned_alloc</a>
                        -
                        <span data-more>allocate aligned memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atexit">atexit</a>
                        -
                        <span data-more>register a function to be called at normal process ter...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/atof">atof</a>
                        -
                        <span data-more>convert a string to a double</span>
                        <span data-less>convert a <code class="language-plaintext highlighter-rouge">string</code> to a <code class="language-plaintext highlighter-rouge">float</code></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/atoi">atoi</a>
                        -
                        <span data-more>convert a string to an integer</span>
                        <span data-less>convert a <code class="language-plaintext highlighter-rouge">string</code> to an <code class="language-plaintext highlighter-rouge">int</code></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/atol">atol</a>
                        -
                        <span data-more>convert a string to an integer</span>
                        <span data-less>convert a <code class="language-plaintext highlighter-rouge">string</code> to a <code class="language-plaintext highlighter-rouge">long</code></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atoll">atoll</a>
                        -
                        <span data-more>convert a string to an integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/atoq">atoq</a>
                        -
                        <span data-more>convert a string to an integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/bsearch">bsearch</a>
                        -
                        <span data-more>binary search of a sorted array</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/calloc">calloc</a>
                        -
                        <span data-more>allocate and free dynamic memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/canonicalize_file_name">canonicalize_file_name</a>
                        -
                        <span data-more>return the canonicalized absolute pathname</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cfree">cfree</a>
                        -
                        <span data-more>free allocated memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clearenv">clearenv</a>
                        -
                        <span data-more>clear the environment</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/div">div</a>
                        -
                        <span data-more>compute quotient and remainder of an integer division</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/drand48">drand48</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/drand48_r">drand48_r</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers r...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ecvt">ecvt</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ecvt_r">ecvt_r</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/erand48">erand48</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/erand48_r">erand48_r</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers r...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/exit">exit</a>
                        -
                        <span data-more>cause normal process termination</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fcvt">fcvt</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fcvt_r">fcvt_r</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/free">free</a>
                        -
                        <span data-more>allocate and free dynamic memory</span>
                        <span data-less>free dynamically allocated memory</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gcvt">gcvt</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getenv">getenv</a>
                        -
                        <span data-more>get an environment variable</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getloadavg">getloadavg</a>
                        -
                        <span data-more>get system load averages</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getpt">getpt</a>
                        -
                        <span data-more>open a new pseudoterminal master</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getsubopt">getsubopt</a>
                        -
                        <span data-more>parse suboption arguments from a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/grantpt">grantpt</a>
                        -
                        <span data-more>grant access to the slave pseudoterminal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/imaxabs">imaxabs</a>
                        -
                        <span data-more>compute the absolute value of an integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/imaxdiv">imaxdiv</a>
                        -
                        <span data-more>compute quotient and remainder of an integer division</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/initstate">initstate</a>
                        -
                        <span data-more>random number generator</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/initstate_r">initstate_r</a>
                        -
                        <span data-more>reentrant random number generator</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/jrand48">jrand48</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/jrand48_r">jrand48_r</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers r...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/l64a">l64a</a>
                        -
                        <span data-more>convert between long and base-64</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/labs">labs</a>
                        -
                        <span data-more>compute the absolute value of an integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lcong48">lcong48</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lcong48_r">lcong48_r</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers r...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ldiv">ldiv</a>
                        -
                        <span data-more>compute quotient and remainder of an integer division</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/llabs">llabs</a>
                        -
                        <span data-more>compute the absolute value of an integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lldiv">lldiv</a>
                        -
                        <span data-more>compute quotient and remainder of an integer division</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lrand48">lrand48</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lrand48_r">lrand48_r</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers r...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/malloc">malloc</a>
                        -
                        <span data-more>allocate and free dynamic memory</span>
                        <span data-less>allocate memory dynamically</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/MB_CUR_MAX">MB_CUR_MAX</a>
                        -
                        <span data-more>maximum length of a multibyte character in the current...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mblen">mblen</a>
                        -
                        <span data-more>determine number of bytes in next multibyte character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mbstowcs">mbstowcs</a>
                        -
                        <span data-more>convert a multibyte string to a wide-character string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mbtowc">mbtowc</a>
                        -
                        <span data-more>convert a multibyte sequence to a wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memalign">memalign</a>
                        -
                        <span data-more>allocate aligned memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mkdtemp">mkdtemp</a>
                        -
                        <span data-more>create a unique temporary directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mkostemp">mkostemp</a>
                        -
                        <span data-more>create a unique temporary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mkostemps">mkostemps</a>
                        -
                        <span data-more>create a unique temporary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mkstemp">mkstemp</a>
                        -
                        <span data-more>create a unique temporary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mkstemps">mkstemps</a>
                        -
                        <span data-more>create a unique temporary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mktemp">mktemp</a>
                        -
                        <span data-more>make a unique temporary filename</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mrand48">mrand48</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mrand48_r">mrand48_r</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers r...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nrand48">nrand48</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/nrand48_r">nrand48_r</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers r...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/on_exit">on_exit</a>
                        -
                        <span data-more>register a function to be called at normal process ter...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/posix_memalign">posix_memalign</a>
                        -
                        <span data-more>allocate aligned memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/posix_openpt">posix_openpt</a>
                        -
                        <span data-more>open a pseudoterminal device</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ptsname">ptsname</a>
                        -
                        <span data-more>get the name of the slave pseudoterminal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ptsname_r">ptsname_r</a>
                        -
                        <span data-more>get the name of the slave pseudoterminal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putenv">putenv</a>
                        -
                        <span data-more>change or add an environment variable</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pvalloc">pvalloc</a>
                        -
                        <span data-more>allocate aligned memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/qecvt">qecvt</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/qecvt_r">qecvt_r</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/qfcvt">qfcvt</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/qfcvt_r">qfcvt_r</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/qgcvt">qgcvt</a>
                        -
                        <span data-more>convert a floating-point number to a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/qsort">qsort</a>
                        -
                        <span data-more>sort an array</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/qsort_r">qsort_r</a>
                        -
                        <span data-more>sort an array</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rand">rand</a>
                        -
                        <span data-more>pseudo-random number generator</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rand_r">rand_r</a>
                        -
                        <span data-more>pseudo-random number generator</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/random">random</a>
                        -
                        <span data-more>random number generator</span>
                        <span data-less>generate a pseudorandom number</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/random_r">random_r</a>
                        -
                        <span data-more>reentrant random number generator</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/realloc">realloc</a>
                        -
                        <span data-more>allocate and free dynamic memory</span>
                        <span data-less>reallocate memory dynamically</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/reallocarray">reallocarray</a>
                        -
                        <span data-more>allocate and free dynamic memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rpmatch">rpmatch</a>
                        -
                        <span data-more>determine if the answer to a question is affirmative o...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/secure_getenv">secure_getenv</a>
                        -
                        <span data-more>get an environment variable</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/seed48">seed48</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/seed48_r">seed48_r</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers r...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setenv">setenv</a>
                        -
                        <span data-more>change or add an environment variable</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setstate">setstate</a>
                        -
                        <span data-more>random number generator</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setstate_r">setstate_r</a>
                        -
                        <span data-more>reentrant random number generator</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/srand">srand</a>
                        -
                        <span data-more>pseudo-random number generator</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/srand48">srand48</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/srand48_r">srand48_r</a>
                        -
                        <span data-more>generate uniformly distributed pseudo-random numbers r...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/srandom">srandom</a>
                        -
                        <span data-more>random number generator</span>
                        <span data-less>seed pseudorandom number generation</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/srandom_r">srandom_r</a>
                        -
                        <span data-more>reentrant random number generator</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strfromd">strfromd</a>
                        -
                        <span data-more>convert a floating-point value into a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strfromf">strfromf</a>
                        -
                        <span data-more>convert a floating-point value into a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strfroml">strfroml</a>
                        -
                        <span data-more>convert a floating-point value into a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtod">strtod</a>
                        -
                        <span data-more>convert ASCII string to floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtof">strtof</a>
                        -
                        <span data-more>convert ASCII string to floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtol">strtol</a>
                        -
                        <span data-more>convert a string to a long integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtold">strtold</a>
                        -
                        <span data-more>convert ASCII string to floating-point number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtoll">strtoll</a>
                        -
                        <span data-more>convert a string to a long integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtoq">strtoq</a>
                        -
                        <span data-more>convert a string to a long integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtoul">strtoul</a>
                        -
                        <span data-more>convert a string to an unsigned long integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtoull">strtoull</a>
                        -
                        <span data-more>convert a string to an unsigned long integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtouq">strtouq</a>
                        -
                        <span data-more>convert a string to an unsigned long integer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/system">system</a>
                        -
                        <span data-more>execute a shell command</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/unlockpt">unlockpt</a>
                        -
                        <span data-more>unlock a pseudoterminal master/slave pair</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/unsetenv">unsetenv</a>
                        -
                        <span data-more>change or add an environment variable</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/valloc">valloc</a>
                        -
                        <span data-more>allocate aligned memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcstombs">wcstombs</a>
                        -
                        <span data-more>convert a wide-character string to a multibyte string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wctomb">wctomb</a>
                        -
                        <span data-more>convert a wide character to a multibyte sequence</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="string.h">
            <a href="#string.h">string.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/bstring">bstring</a>
                        -
                        <span data-more>byte string operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memccpy">memccpy</a>
                        -
                        <span data-more>copy memory area</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memchr">memchr</a>
                        -
                        <span data-more>scan memory for a character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memcmp">memcmp</a>
                        -
                        <span data-more>compare memory areas</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memcpy">memcpy</a>
                        -
                        <span data-more>copy memory area</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memfrob">memfrob</a>
                        -
                        <span data-more>frobnicate (encrypt) a memory area</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memmem">memmem</a>
                        -
                        <span data-more>locate a substring</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memmove">memmove</a>
                        -
                        <span data-more>copy memory area</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mempcpy">mempcpy</a>
                        -
                        <span data-more>copy memory area</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memrchr">memrchr</a>
                        -
                        <span data-more>scan memory for a character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/memset">memset</a>
                        -
                        <span data-more>fill memory with a constant byte</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rawmemchr">rawmemchr</a>
                        -
                        <span data-more>scan memory for a character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigabbrev_np">sigabbrev_np</a>
                        -
                        <span data-more>return string describing signal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sigdescr_np">sigdescr_np</a>
                        -
                        <span data-more>return string describing signal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/stpcpy">stpcpy</a>
                        -
                        <span data-more>copy a string returning a pointer to its end</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/stpncpy">stpncpy</a>
                        -
                        <span data-more>copy a fixed-size string, returning a pointer to its end</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/strcasestr">strcasestr</a>
                        -
                        <span data-more>locate a substring</span>
                        <span data-less>locate a substring</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strcat">strcat</a>
                        -
                        <span data-more>concatenate two strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strchr">strchr</a>
                        -
                        <span data-more>locate character in string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strchrnul">strchrnul</a>
                        -
                        <span data-more>locate character in string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/strcmp">strcmp</a>
                        -
                        <span data-more>compare two strings</span>
                        <span data-less>compare two strings</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strcoll">strcoll</a>
                        -
                        <span data-more>compare two strings using the current locale</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/strcpy">strcpy</a>
                        -
                        <span data-more>copy a string</span>
                        <span data-less>copy a string</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strcspn">strcspn</a>
                        -
                        <span data-more>get length of a prefix substring</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strdup">strdup</a>
                        -
                        <span data-more>duplicate a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strdupa">strdupa</a>
                        -
                        <span data-more>duplicate a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strerror">strerror</a>
                        -
                        <span data-more>return string describing error number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strerror_l">strerror_l</a>
                        -
                        <span data-more>return string describing error number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strerror_r">strerror_r</a>
                        -
                        <span data-more>return string describing error number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strerrordesc_np">strerrordesc_np</a>
                        -
                        <span data-more>return string describing error number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strerrorname_np">strerrorname_np</a>
                        -
                        <span data-more>return string describing error number</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strfry">strfry</a>
                        -
                        <span data-more>randomize a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/strlen">strlen</a>
                        -
                        <span data-more>calculate the length of a string</span>
                        <span data-less>calculate the length of a string</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strncat">strncat</a>
                        -
                        <span data-more>concatenate two strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strncmp">strncmp</a>
                        -
                        <span data-more>compare two strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strncpy">strncpy</a>
                        -
                        <span data-more>copy a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strndup">strndup</a>
                        -
                        <span data-more>duplicate a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strndupa">strndupa</a>
                        -
                        <span data-more>duplicate a string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strnlen">strnlen</a>
                        -
                        <span data-more>determine the length of a fixed-size string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strpbrk">strpbrk</a>
                        -
                        <span data-more>search a string for any of a set of bytes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strrchr">strrchr</a>
                        -
                        <span data-more>locate character in string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strsep">strsep</a>
                        -
                        <span data-more>extract token from string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strsignal">strsignal</a>
                        -
                        <span data-more>return string describing signal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strspn">strspn</a>
                        -
                        <span data-more>get length of a prefix substring</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/strstr">strstr</a>
                        -
                        <span data-more>locate a substring</span>
                        <span data-less>locate a substring</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtok">strtok</a>
                        -
                        <span data-more>extract tokens from strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strtok_r">strtok_r</a>
                        -
                        <span data-more>extract tokens from strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strverscmp">strverscmp</a>
                        -
                        <span data-more>compare two version strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strxfrm">strxfrm</a>
                        -
                        <span data-more>string transformation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sys_siglist">sys_siglist</a>
                        -
                        <span data-more>return string describing signal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wmempcpy">wmempcpy</a>
                        -
                        <span data-more>copy memory area</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="strings.h">
            <a href="#strings.h">strings.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/bcmp">bcmp</a>
                        -
                        <span data-more>compare byte sequences</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/bcopy">bcopy</a>
                        -
                        <span data-more>copy byte sequence</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/bzero">bzero</a>
                        -
                        <span data-more>zero a byte string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/explicit_bzero">explicit_bzero</a>
                        -
                        <span data-more>zero a byte string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ffs">ffs</a>
                        -
                        <span data-more>find first bit set in a word</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ffsl">ffsl</a>
                        -
                        <span data-more>find first bit set in a word</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ffsll">ffsll</a>
                        -
                        <span data-more>find first bit set in a word</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/index">index</a>
                        -
                        <span data-more>locate character in string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rindex">rindex</a>
                        -
                        <span data-more>locate character in string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="3/strcasecmp">strcasecmp</a>
                        -
                        <span data-more>compare two strings ignoring case</span>
                        <span data-less>compare two strings ignoring case</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/string">string</a>
                        -
                        <span data-more>string operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strncasecmp">strncasecmp</a>
                        -
                        <span data-more>compare two strings ignoring case</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/ipc.h">
            <a href="#sys/ipc.h">sys/ipc.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/shmctl">shmctl</a>
                        -
                        <span data-more>System V shared memory control</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/shmget">shmget</a>
                        -
                        <span data-more>allocates a System V shared memory segment</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/mman.h">
            <a href="#sys/mman.h">sys/mman.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/madvise">madvise</a>
                        -
                        <span data-more>give advice about use of memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/memfd_create">memfd_create</a>
                        -
                        <span data-more>create an anonymous file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mlock">mlock</a>
                        -
                        <span data-more>lock and unlock memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mlock2">mlock2</a>
                        -
                        <span data-more>lock and unlock memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mlockall">mlockall</a>
                        -
                        <span data-more>lock and unlock memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mmap">mmap</a>
                        -
                        <span data-more>map or unmap files or devices into memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mmap2">mmap2</a>
                        -
                        <span data-more>map files or devices into memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mmap64">mmap64</a>
                        -
                        <span data-more>map or unmap files or devices into memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mprotect">mprotect</a>
                        -
                        <span data-more>set protection on a region of memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mremap">mremap</a>
                        -
                        <span data-more>remap a virtual memory address</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/msync">msync</a>
                        -
                        <span data-more>synchronize a file with a memory map</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/munlock">munlock</a>
                        -
                        <span data-more>lock and unlock memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/munlockall">munlockall</a>
                        -
                        <span data-more>lock and unlock memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/munmap">munmap</a>
                        -
                        <span data-more>map or unmap files or devices into memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pkey_alloc">pkey_alloc</a>
                        -
                        <span data-more>allocate or free a protection key</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pkey_free">pkey_free</a>
                        -
                        <span data-more>allocate or free a protection key</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pkey_mprotect">pkey_mprotect</a>
                        -
                        <span data-more>set protection on a region of memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/posix_madvise">posix_madvise</a>
                        -
                        <span data-more>give advice about patterns of memory usage</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/remap_file_pages">remap_file_pages</a>
                        -
                        <span data-more>create a nonlinear file mapping</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/shm_open">shm_open</a>
                        -
                        <span data-more>create/open or unlink POSIX shared memory objects</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/shm_unlink">shm_unlink</a>
                        -
                        <span data-more>create/open or unlink POSIX shared memory objects</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/select.h">
            <a href="#sys/select.h">sys/select.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/_newselect">_newselect</a>
                        -
                        <span data-more>synchronous I/O multiplexing</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/FD_CLR">FD_CLR</a>
                        -
                        <span data-more>synchronous I/O multiplexing</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/FD_ISSET">FD_ISSET</a>
                        -
                        <span data-more>synchronous I/O multiplexing</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/FD_SET">FD_SET</a>
                        -
                        <span data-more>synchronous I/O multiplexing</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/FD_ZERO">FD_ZERO</a>
                        -
                        <span data-more>synchronous I/O multiplexing</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pselect">pselect</a>
                        -
                        <span data-more>synchronous I/O multiplexing</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pselect6">pselect6</a>
                        -
                        <span data-more>synchronous I/O multiplexing</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/select">select</a>
                        -
                        <span data-more>synchronous I/O multiplexing</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/socket.h">
            <a href="#sys/socket.h">sys/socket.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/accept">accept</a>
                        -
                        <span data-more>accept a connection on a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/accept4">accept4</a>
                        -
                        <span data-more>accept a connection on a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/address_families">address_families</a>
                        -
                        <span data-more>socket address families (domains)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/bind">bind</a>
                        -
                        <span data-more>bind a name to a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cmsg">cmsg</a>
                        -
                        <span data-more>access ancillary data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CMSG_ALIGN">CMSG_ALIGN</a>
                        -
                        <span data-more>access ancillary data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CMSG_DATA">CMSG_DATA</a>
                        -
                        <span data-more>access ancillary data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CMSG_FIRSTHDR">CMSG_FIRSTHDR</a>
                        -
                        <span data-more>access ancillary data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CMSG_LEN">CMSG_LEN</a>
                        -
                        <span data-more>access ancillary data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CMSG_NXTHDR">CMSG_NXTHDR</a>
                        -
                        <span data-more>access ancillary data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/CMSG_SPACE">CMSG_SPACE</a>
                        -
                        <span data-more>access ancillary data</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/connect">connect</a>
                        -
                        <span data-more>initiate a connection on a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/ddp">ddp</a>
                        -
                        <span data-more>Linux AppleTalk protocol implementation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getnameinfo">getnameinfo</a>
                        -
                        <span data-more>address-to-name translation in protocol-independent ma...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getpeername">getpeername</a>
                        -
                        <span data-more>get name of connected peer socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getsockname">getsockname</a>
                        -
                        <span data-more>get socket name</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getsockopt">getsockopt</a>
                        -
                        <span data-more>get and set options on sockets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet">inet</a>
                        -
                        <span data-more>Internet address manipulation routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_addr">inet_addr</a>
                        -
                        <span data-more>Internet address manipulation routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_aton">inet_aton</a>
                        -
                        <span data-more>Internet address manipulation routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_lnaof">inet_lnaof</a>
                        -
                        <span data-more>Internet address manipulation routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_makeaddr">inet_makeaddr</a>
                        -
                        <span data-more>Internet address manipulation routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_netof">inet_netof</a>
                        -
                        <span data-more>Internet address manipulation routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_network">inet_network</a>
                        -
                        <span data-more>Internet address manipulation routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/inet_ntoa">inet_ntoa</a>
                        -
                        <span data-more>Internet address manipulation routines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/ip">ip</a>
                        -
                        <span data-more>Linux IPv4 protocol implementation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/ipv6">ipv6</a>
                        -
                        <span data-more>Linux IPv6 protocol implementation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/listen">listen</a>
                        -
                        <span data-more>listen for connections on a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/packet">packet</a>
                        -
                        <span data-more>packet interface on device level</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/raw">raw</a>
                        -
                        <span data-more>Linux IPv4 raw sockets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setsockopt">setsockopt</a>
                        -
                        <span data-more>get and set options on sockets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/shutdown">shutdown</a>
                        -
                        <span data-more>shut down part of a full-duplex connection</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/sock_diag">sock_diag</a>
                        -
                        <span data-more>obtaining information about sockets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sockatmark">sockatmark</a>
                        -
                        <span data-more>determine whether socket is at out-of-band mark</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/socket">socket</a>
                        -
                        <span data-more>create an endpoint for communication</span>
                        <span data-less></span>
                    </li>

                

                    

                    <li>
                        <a href="7/socket">socket</a>
                        -
                        <span data-more>Linux socket interface</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/socketpair">socketpair</a>
                        -
                        <span data-more>create a pair of connected sockets</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/tcp">tcp</a>
                        -
                        <span data-more>TCP protocol</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/udp">udp</a>
                        -
                        <span data-more>User Datagram Protocol for IPv4</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/udplite">udplite</a>
                        -
                        <span data-more>Lightweight User Datagram Protocol</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/unix">unix</a>
                        -
                        <span data-more>sockets for local interprocess communication</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/vsock">vsock</a>
                        -
                        <span data-more>Linux VSOCK address family</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="7/x25">x25</a>
                        -
                        <span data-more>ITU-T X.25 / ISO-8208 protocol interface</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/stat.h">
            <a href="#sys/stat.h">sys/stat.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/chmod">chmod</a>
                        -
                        <span data-more>change permissions of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fchmod">fchmod</a>
                        -
                        <span data-more>change permissions of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fchmodat">fchmodat</a>
                        -
                        <span data-more>change permissions of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isfdtype">isfdtype</a>
                        -
                        <span data-more>test file type of a file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mkdir">mkdir</a>
                        -
                        <span data-more>create a directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mkdirat">mkdirat</a>
                        -
                        <span data-more>create a directory</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/statvfs.h">
            <a href="#sys/statvfs.h">sys/statvfs.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/fstatvfs">fstatvfs</a>
                        -
                        <span data-more>get filesystem statistics</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/statvfs">statvfs</a>
                        -
                        <span data-more>get filesystem statistics</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/time.h">
            <a href="#sys/time.h">sys/time.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/adjtime">adjtime</a>
                        -
                        <span data-more>correct the time to synchronize the system clock</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/futimes">futimes</a>
                        -
                        <span data-more>change file timestamps</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getitimer">getitimer</a>
                        -
                        <span data-more>get or set value of an interval timer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getpriority">getpriority</a>
                        -
                        <span data-more>get/set program scheduling priority</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getrlimit">getrlimit</a>
                        -
                        <span data-more>get/set resource limits</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getrusage">getrusage</a>
                        -
                        <span data-more>get resource usage</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/gettimeofday">gettimeofday</a>
                        -
                        <span data-more>get / set time</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lutimes">lutimes</a>
                        -
                        <span data-more>change file timestamps</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/prlimit">prlimit</a>
                        -
                        <span data-more>get/set resource limits</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/prlimit64">prlimit64</a>
                        -
                        <span data-more>get/set resource limits</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setitimer">setitimer</a>
                        -
                        <span data-more>get or set value of an interval timer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setpriority">setpriority</a>
                        -
                        <span data-more>get/set program scheduling priority</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setrlimit">setrlimit</a>
                        -
                        <span data-more>get/set resource limits</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/settimeofday">settimeofday</a>
                        -
                        <span data-more>get / set time</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/timeradd">timeradd</a>
                        -
                        <span data-more>timeval operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/timerclear">timerclear</a>
                        -
                        <span data-more>timeval operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/timercmp">timercmp</a>
                        -
                        <span data-more>timeval operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/timerisset">timerisset</a>
                        -
                        <span data-more>timeval operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/timersub">timersub</a>
                        -
                        <span data-more>timeval operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/ugetrlimit">ugetrlimit</a>
                        -
                        <span data-more>get/set resource limits</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vlimit">vlimit</a>
                        -
                        <span data-more>get/set resource limits</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vtimes">vtimes</a>
                        -
                        <span data-more>get resource usage</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/times.h">
            <a href="#sys/times.h">sys/times.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/times">times</a>
                        -
                        <span data-more>get process times</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/types.h">
            <a href="#sys/types.h">sys/types.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/_llseek">_llseek</a>
                        -
                        <span data-more>reposition read/write file offset</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/add_key">add_key</a>
                        -
                        <span data-more>add a key to the kernel&#39;s key management facility</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/bindresvport">bindresvport</a>
                        -
                        <span data-more>bind a socket to a privileged IP port</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/closedir">closedir</a>
                        -
                        <span data-more>close a directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/creat">creat</a>
                        -
                        <span data-more>open and possibly create a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/db">db</a>
                        -
                        <span data-more>database access methods</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dbopen">dbopen</a>
                        -
                        <span data-more>database access methods</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dirfd">dirfd</a>
                        -
                        <span data-more>get directory stream file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/endgrent">endgrent</a>
                        -
                        <span data-more>get group file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/endpwent">endpwent</a>
                        -
                        <span data-more>get password file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fdopendir">fdopendir</a>
                        -
                        <span data-more>open a directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fgetxattr">fgetxattr</a>
                        -
                        <span data-more>retrieve an extended attribute value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/flistxattr">flistxattr</a>
                        -
                        <span data-more>list extended attribute names</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fork">fork</a>
                        -
                        <span data-more>create a child process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/freeaddrinfo">freeaddrinfo</a>
                        -
                        <span data-more>network address and service translation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/freehostent">freehostent</a>
                        -
                        <span data-more>get network hostnames and addresses</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/freeifaddrs">freeifaddrs</a>
                        -
                        <span data-more>get interface addresses</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fremovexattr">fremovexattr</a>
                        -
                        <span data-more>remove an extended attribute</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fsetxattr">fsetxattr</a>
                        -
                        <span data-more>set an extended attribute value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fstat">fstat</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fstat64">fstat64</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fstatat">fstatat</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fstatat64">fstatat64</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ftok">ftok</a>
                        -
                        <span data-more>convert a pathname and a project identifier to a Syste...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fts">fts</a>
                        -
                        <span data-more>traverse a file hierarchy</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fts_children">fts_children</a>
                        -
                        <span data-more>traverse a file hierarchy</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fts_close">fts_close</a>
                        -
                        <span data-more>traverse a file hierarchy</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fts_open">fts_open</a>
                        -
                        <span data-more>traverse a file hierarchy</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fts_read">fts_read</a>
                        -
                        <span data-more>traverse a file hierarchy</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fts_set">fts_set</a>
                        -
                        <span data-more>traverse a file hierarchy</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gai_strerror">gai_strerror</a>
                        -
                        <span data-more>network address and service translation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getaddrinfo">getaddrinfo</a>
                        -
                        <span data-more>network address and service translation</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getgrent">getgrent</a>
                        -
                        <span data-more>get group file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getgrgid">getgrgid</a>
                        -
                        <span data-more>get group file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getgrgid_r">getgrgid_r</a>
                        -
                        <span data-more>get group file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getgrnam">getgrnam</a>
                        -
                        <span data-more>get group file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getgrnam_r">getgrnam_r</a>
                        -
                        <span data-more>get group file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getgroups">getgroups</a>
                        -
                        <span data-more>get/set list of supplementary group IDs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getgroups32">getgroups32</a>
                        -
                        <span data-more>get/set list of supplementary group IDs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getifaddrs">getifaddrs</a>
                        -
                        <span data-more>get interface addresses</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getipnodebyaddr">getipnodebyaddr</a>
                        -
                        <span data-more>get network hostnames and addresses</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getipnodebyname">getipnodebyname</a>
                        -
                        <span data-more>get network hostnames and addresses</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getpgid">getpgid</a>
                        -
                        <span data-more>set/get process group</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getpgrp">getpgrp</a>
                        -
                        <span data-more>set/get process group</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getpid">getpid</a>
                        -
                        <span data-more>get process identification</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getppid">getppid</a>
                        -
                        <span data-more>get process identification</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getpw">getpw</a>
                        -
                        <span data-more>reconstruct password line entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getpwent">getpwent</a>
                        -
                        <span data-more>get password file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getpwnam">getpwnam</a>
                        -
                        <span data-more>get password file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getpwnam_r">getpwnam_r</a>
                        -
                        <span data-more>get password file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getpwuid">getpwuid</a>
                        -
                        <span data-more>get password file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getpwuid_r">getpwuid_r</a>
                        -
                        <span data-more>get password file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getsid">getsid</a>
                        -
                        <span data-more>get session ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getumask">getumask</a>
                        -
                        <span data-more>get file creation mask</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getxattr">getxattr</a>
                        -
                        <span data-more>retrieve an extended attribute value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/initgroups">initgroups</a>
                        -
                        <span data-more>initialize the supplementary group access list</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/keyctl">keyctl</a>
                        -
                        <span data-more>manipulate the kernel&#39;s key management facility</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/kill">kill</a>
                        -
                        <span data-more>send signal to a process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/lgetxattr">lgetxattr</a>
                        -
                        <span data-more>retrieve an extended attribute value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/listxattr">listxattr</a>
                        -
                        <span data-more>list extended attribute names</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/llistxattr">llistxattr</a>
                        -
                        <span data-more>list extended attribute names</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/llseek">llseek</a>
                        -
                        <span data-more>reposition read/write file offset</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/lremovexattr">lremovexattr</a>
                        -
                        <span data-more>remove an extended attribute</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/lseek">lseek</a>
                        -
                        <span data-more>reposition read/write file offset</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lseek64">lseek64</a>
                        -
                        <span data-more>reposition 64-bit read/write file offset</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/lsetxattr">lsetxattr</a>
                        -
                        <span data-more>set an extended attribute value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/lstat">lstat</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/lstat64">lstat64</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mkfifo">mkfifo</a>
                        -
                        <span data-more>make a FIFO special file (a named pipe)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mkfifoat">mkfifoat</a>
                        -
                        <span data-more>make a FIFO special file (a named pipe)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mknod">mknod</a>
                        -
                        <span data-more>create a special or ordinary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mknodat">mknodat</a>
                        -
                        <span data-more>create a special or ordinary file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/modify_ldt">modify_ldt</a>
                        -
                        <span data-more>get or set a per-process LDT entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mq_getsetattr">mq_getsetattr</a>
                        -
                        <span data-more>get/set message queue attributes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/msgctl">msgctl</a>
                        -
                        <span data-more>System V message control operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/msgget">msgget</a>
                        -
                        <span data-more>get a System V message queue identifier</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/msgop">msgop</a>
                        -
                        <span data-more>System V message queue operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/msgrcv">msgrcv</a>
                        -
                        <span data-more>System V message queue operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/msgsnd">msgsnd</a>
                        -
                        <span data-more>System V message queue operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/name_to_handle_at">name_to_handle_at</a>
                        -
                        <span data-more>obtain handle for a pathname and open file via a handle</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/newfstatat">newfstatat</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/oldfstat">oldfstat</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/oldlstat">oldlstat</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/oldstat">oldstat</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/open">open</a>
                        -
                        <span data-more>open and possibly create a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/open_by_handle_at">open_by_handle_at</a>
                        -
                        <span data-more>obtain handle for a pathname and open file via a handle</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/openat">openat</a>
                        -
                        <span data-more>open and possibly create a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/openat2">openat2</a>
                        -
                        <span data-more>open and possibly create a file (extended)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/opendir">opendir</a>
                        -
                        <span data-more>open a directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pidfd_open">pidfd_open</a>
                        -
                        <span data-more>obtain a file descriptor that refers to a process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/re_comp">re_comp</a>
                        -
                        <span data-more>BSD regex functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/re_exec">re_exec</a>
                        -
                        <span data-more>BSD regex functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/recv">recv</a>
                        -
                        <span data-more>receive a message from a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/recvfrom">recvfrom</a>
                        -
                        <span data-more>receive a message from a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/recvmsg">recvmsg</a>
                        -
                        <span data-more>receive a message from a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/removexattr">removexattr</a>
                        -
                        <span data-more>remove an extended attribute</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/request_key">request_key</a>
                        -
                        <span data-more>request a key from the kernel&#39;s key management facility</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/rewinddir">rewinddir</a>
                        -
                        <span data-more>reset directory stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/semctl">semctl</a>
                        -
                        <span data-more>System V semaphore control operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/semget">semget</a>
                        -
                        <span data-more>get a System V semaphore set identifier</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/semop">semop</a>
                        -
                        <span data-more>System V semaphore operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/semtimedop">semtimedop</a>
                        -
                        <span data-more>System V semaphore operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/send">send</a>
                        -
                        <span data-more>send a message on a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sendmsg">sendmsg</a>
                        -
                        <span data-more>send a message on a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sendto">sendto</a>
                        -
                        <span data-more>send a message on a socket</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setegid">setegid</a>
                        -
                        <span data-more>set effective user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/seteuid">seteuid</a>
                        -
                        <span data-more>set effective user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setgid">setgid</a>
                        -
                        <span data-more>set group identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setgid32">setgid32</a>
                        -
                        <span data-more>set group identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setgrent">setgrent</a>
                        -
                        <span data-more>get group file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setgroups">setgroups</a>
                        -
                        <span data-more>get/set list of supplementary group IDs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setgroups32">setgroups32</a>
                        -
                        <span data-more>get/set list of supplementary group IDs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setpgid">setpgid</a>
                        -
                        <span data-more>set/get process group</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setpgrp">setpgrp</a>
                        -
                        <span data-more>set/get process group</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setpwent">setpwent</a>
                        -
                        <span data-more>get password file entry</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setregid">setregid</a>
                        -
                        <span data-more>set real and/or effective user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setregid32">setregid32</a>
                        -
                        <span data-more>set real and/or effective user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setreuid">setreuid</a>
                        -
                        <span data-more>set real and/or effective user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setreuid32">setreuid32</a>
                        -
                        <span data-more>set real and/or effective user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setsid">setsid</a>
                        -
                        <span data-more>creates a session and sets the process group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setuid">setuid</a>
                        -
                        <span data-more>set user identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setuid32">setuid32</a>
                        -
                        <span data-more>set user identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setxattr">setxattr</a>
                        -
                        <span data-more>set an extended attribute value</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/shmat">shmat</a>
                        -
                        <span data-more>System V shared memory operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/shmdt">shmdt</a>
                        -
                        <span data-more>System V shared memory operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/shmop">shmop</a>
                        -
                        <span data-more>System V shared memory operations</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/spu_create">spu_create</a>
                        -
                        <span data-more>create a new spu context</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/stat">stat</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/stat64">stat64</a>
                        -
                        <span data-more>get file status</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/statx">statx</a>
                        -
                        <span data-more>get file status (extended)</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/umask">umask</a>
                        -
                        <span data-more>set file mode creation mask</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/userfaultfd">userfaultfd</a>
                        -
                        <span data-more>create a file descriptor for handling page faults in u...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/ustat">ustat</a>
                        -
                        <span data-more>get filesystem statistics</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/utime">utime</a>
                        -
                        <span data-more>change file last access and modification times</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/utimes">utimes</a>
                        -
                        <span data-more>change file last access and modification times</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/vfork">vfork</a>
                        -
                        <span data-more>create a child process and block parent</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/wait">wait</a>
                        -
                        <span data-more>wait for process to change state</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/wait3">wait3</a>
                        -
                        <span data-more>wait for process to change state, BSD style</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/wait4">wait4</a>
                        -
                        <span data-more>wait for process to change state, BSD style</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/waitid">waitid</a>
                        -
                        <span data-more>wait for process to change state</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/waitpid">waitpid</a>
                        -
                        <span data-more>wait for process to change state</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/uio.h">
            <a href="#sys/uio.h">sys/uio.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/preadv">preadv</a>
                        -
                        <span data-more>read or write data into multiple buffers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/preadv2">preadv2</a>
                        -
                        <span data-more>read or write data into multiple buffers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/process_vm_readv">process_vm_readv</a>
                        -
                        <span data-more>transfer data between process address spaces</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/process_vm_writev">process_vm_writev</a>
                        -
                        <span data-more>transfer data between process address spaces</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pwritev">pwritev</a>
                        -
                        <span data-more>read or write data into multiple buffers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pwritev2">pwritev2</a>
                        -
                        <span data-more>read or write data into multiple buffers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/readv">readv</a>
                        -
                        <span data-more>read or write data into multiple buffers</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/writev">writev</a>
                        -
                        <span data-more>read or write data into multiple buffers</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="sys/utsname.h">
            <a href="#sys/utsname.h">sys/utsname.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/oldolduname">oldolduname</a>
                        -
                        <span data-more>get name and information about current kernel</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/olduname">olduname</a>
                        -
                        <span data-more>get name and information about current kernel</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/uname">uname</a>
                        -
                        <span data-more>get name and information about current kernel</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="syslog.h">
            <a href="#syslog.h">syslog.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/closelog">closelog</a>
                        -
                        <span data-more>send messages to the system logger</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/openlog">openlog</a>
                        -
                        <span data-more>send messages to the system logger</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setlogmask">setlogmask</a>
                        -
                        <span data-more>set log priority mask</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/syslog">syslog</a>
                        -
                        <span data-more>read and/or clear kernel message ring buffer; set cons...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/vsyslog">vsyslog</a>
                        -
                        <span data-more>send messages to the system logger</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="termios.h">
            <a href="#termios.h">termios.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/cfgetispeed">cfgetispeed</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cfgetospeed">cfgetospeed</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cfmakeraw">cfmakeraw</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cfsetispeed">cfsetispeed</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cfsetospeed">cfsetospeed</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cfsetspeed">cfsetspeed</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/ioctl_tty">ioctl_tty</a>
                        -
                        <span data-more>ioctls for terminals and serial lines</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tcdrain">tcdrain</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tcflow">tcflow</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tcflush">tcflush</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tcgetattr">tcgetattr</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tcgetsid">tcgetsid</a>
                        -
                        <span data-more>get session ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tcsendbreak">tcsendbreak</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tcsetattr">tcsetattr</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/termios">termios</a>
                        -
                        <span data-more>get and set terminal attributes, line control, get and...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="4/tty_ioctl">tty_ioctl</a>
                        -
                        <span data-more>ioctls for terminals and serial lines</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="time.h">
            <a href="#time.h">time.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/asctime">asctime</a>
                        -
                        <span data-more>transform date and time to broken-down time or ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/asctime_r">asctime_r</a>
                        -
                        <span data-more>transform date and time to broken-down time or ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clock">clock</a>
                        -
                        <span data-more>determine processor time</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/clock_getcpuclockid">clock_getcpuclockid</a>
                        -
                        <span data-more>obtain ID of a process CPU-time clock</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/clock_getres">clock_getres</a>
                        -
                        <span data-more>clock and time functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/clock_gettime">clock_gettime</a>
                        -
                        <span data-more>clock and time functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/clock_nanosleep">clock_nanosleep</a>
                        -
                        <span data-more>high-resolution sleep with specifiable clock</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/clock_settime">clock_settime</a>
                        -
                        <span data-more>clock and time functions</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ctime">ctime</a>
                        -
                        <span data-more>transform date and time to broken-down time or ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ctime_r">ctime_r</a>
                        -
                        <span data-more>transform date and time to broken-down time or ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/daylight">daylight</a>
                        -
                        <span data-more>initialize time conversion information</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/difftime">difftime</a>
                        -
                        <span data-more>calculate time difference</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/dysize">dysize</a>
                        -
                        <span data-more>get number of days for a given year</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getdate">getdate</a>
                        -
                        <span data-more>convert a date-plus-time string to broken-down time</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getdate_err">getdate_err</a>
                        -
                        <span data-more>convert a date-plus-time string to broken-down time</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getdate_r">getdate_r</a>
                        -
                        <span data-more>convert a date-plus-time string to broken-down time</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gmtime">gmtime</a>
                        -
                        <span data-more>transform date and time to broken-down time or ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gmtime_r">gmtime_r</a>
                        -
                        <span data-more>transform date and time to broken-down time or ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/localtime">localtime</a>
                        -
                        <span data-more>transform date and time to broken-down time or ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/localtime_r">localtime_r</a>
                        -
                        <span data-more>transform date and time to broken-down time or ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mktime">mktime</a>
                        -
                        <span data-more>transform date and time to broken-down time or ASCII</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/nanosleep">nanosleep</a>
                        -
                        <span data-more>high-resolution sleep</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/stime">stime</a>
                        -
                        <span data-more>set time</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strftime">strftime</a>
                        -
                        <span data-more>format date and time</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/strptime">strptime</a>
                        -
                        <span data-more>convert a string representation of time to a time tm s...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li data-filter>
                        <a href="2/time">time</a>
                        -
                        <span data-more>get time in seconds</span>
                        <span data-less>get time in seconds</span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/timegm">timegm</a>
                        -
                        <span data-more>inverses of gmtime and localtime</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/timelocal">timelocal</a>
                        -
                        <span data-more>inverses of gmtime and localtime</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/timer_delete">timer_delete</a>
                        -
                        <span data-more>delete a POSIX per-process timer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/timer_getoverrun">timer_getoverrun</a>
                        -
                        <span data-more>get overrun count for a POSIX per-process timer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/timer_gettime">timer_gettime</a>
                        -
                        <span data-more>arm/disarm and fetch state of POSIX per-process timer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/timer_settime">timer_settime</a>
                        -
                        <span data-more>arm/disarm and fetch state of POSIX per-process timer</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/timezone">timezone</a>
                        -
                        <span data-more>initialize time conversion information</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tzname">tzname</a>
                        -
                        <span data-more>initialize time conversion information</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tzset">tzset</a>
                        -
                        <span data-more>initialize time conversion information</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="ulimit.h">
            <a href="#ulimit.h">ulimit.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/ulimit">ulimit</a>
                        -
                        <span data-more>get and set user limits</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="unistd.h">
            <a href="#unistd.h">unistd.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="2/_Exit">_Exit</a>
                        -
                        <span data-more>terminate the calling process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/_exit">_exit</a>
                        -
                        <span data-more>terminate the calling process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/_sysctl">_sysctl</a>
                        -
                        <span data-more>read/write system parameters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/access">access</a>
                        -
                        <span data-more>check user&#39;s permissions for a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/acct">acct</a>
                        -
                        <span data-more>switch process accounting on or off</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/alarm">alarm</a>
                        -
                        <span data-more>set an alarm clock for delivery of a signal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/brk">brk</a>
                        -
                        <span data-more>change data segment size</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/chdir">chdir</a>
                        -
                        <span data-more>change working directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/chown">chown</a>
                        -
                        <span data-more>change ownership of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/chown32">chown32</a>
                        -
                        <span data-more>change ownership of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/chroot">chroot</a>
                        -
                        <span data-more>change root directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/close">close</a>
                        -
                        <span data-more>close a file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/confstr">confstr</a>
                        -
                        <span data-more>get configuration dependent string variables</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/copy_file_range">copy_file_range</a>
                        -
                        <span data-more>Copy a range of data from one file to another</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/cuserid">cuserid</a>
                        -
                        <span data-more>get username</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/daemon">daemon</a>
                        -
                        <span data-more>run in the background</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/dup">dup</a>
                        -
                        <span data-more>duplicate a file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/dup2">dup2</a>
                        -
                        <span data-more>duplicate a file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/dup3">dup3</a>
                        -
                        <span data-more>duplicate a file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/eaccess">eaccess</a>
                        -
                        <span data-more>check effective user&#39;s permissions for a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/encrypt">encrypt</a>
                        -
                        <span data-more>encrypt 64-bit messages</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/encrypt_r">encrypt_r</a>
                        -
                        <span data-more>encrypt 64-bit messages</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/endusershell">endusershell</a>
                        -
                        <span data-more>get permitted user shells</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/euidaccess">euidaccess</a>
                        -
                        <span data-more>check effective user&#39;s permissions for a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/exec">exec</a>
                        -
                        <span data-more>execute a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/execl">execl</a>
                        -
                        <span data-more>execute a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/execle">execle</a>
                        -
                        <span data-more>execute a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/execlp">execlp</a>
                        -
                        <span data-more>execute a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/execv">execv</a>
                        -
                        <span data-more>execute a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/execve">execve</a>
                        -
                        <span data-more>execute program</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/execveat">execveat</a>
                        -
                        <span data-more>execute program relative to a directory file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/execvp">execvp</a>
                        -
                        <span data-more>execute a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/execvpe">execvpe</a>
                        -
                        <span data-more>execute a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/exit">exit</a>
                        -
                        <span data-more>terminate the calling process</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/faccessat">faccessat</a>
                        -
                        <span data-more>check user&#39;s permissions for a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/faccessat2">faccessat2</a>
                        -
                        <span data-more>check user&#39;s permissions for a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fchdir">fchdir</a>
                        -
                        <span data-more>change working directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fchown">fchown</a>
                        -
                        <span data-more>change ownership of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fchown32">fchown32</a>
                        -
                        <span data-more>change ownership of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fchownat">fchownat</a>
                        -
                        <span data-more>change ownership of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fcntl">fcntl</a>
                        -
                        <span data-more>manipulate file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fcntl64">fcntl64</a>
                        -
                        <span data-more>manipulate file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fdatasync">fdatasync</a>
                        -
                        <span data-more>synchronize a file&#39;s in-core state with storage device</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fexecve">fexecve</a>
                        -
                        <span data-more>execute program specified via file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fpathconf">fpathconf</a>
                        -
                        <span data-more>get configuration values for files</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/fsync">fsync</a>
                        -
                        <span data-more>synchronize a file&#39;s in-core state with storage device</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/ftruncate">ftruncate</a>
                        -
                        <span data-more>truncate a file to a specified length</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/ftruncate64">ftruncate64</a>
                        -
                        <span data-more>truncate a file to a specified length</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/get_current_dir_name">get_current_dir_name</a>
                        -
                        <span data-more>get current working directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getcwd">getcwd</a>
                        -
                        <span data-more>get current working directory</span>
                        <span data-less></span>
                    </li>

                

                    

                    <li>
                        <a href="3/getcwd">getcwd</a>
                        -
                        <span data-more>get current working directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getdomainname">getdomainname</a>
                        -
                        <span data-more>get/set NIS domain name</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getdtablesize">getdtablesize</a>
                        -
                        <span data-more>get file descriptor table size</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getegid">getegid</a>
                        -
                        <span data-more>get group identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getegid32">getegid32</a>
                        -
                        <span data-more>get group identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getentropy">getentropy</a>
                        -
                        <span data-more>fill a buffer with random bytes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/geteuid">geteuid</a>
                        -
                        <span data-more>get user identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/geteuid32">geteuid32</a>
                        -
                        <span data-more>get user identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getgid">getgid</a>
                        -
                        <span data-more>get group identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getgid32">getgid32</a>
                        -
                        <span data-more>get group identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/gethostid">gethostid</a>
                        -
                        <span data-more>get or set the unique identifier of the current host</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/gethostname">gethostname</a>
                        -
                        <span data-more>get/set hostname</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getlogin">getlogin</a>
                        -
                        <span data-more>get username</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getlogin_r">getlogin_r</a>
                        -
                        <span data-more>get username</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getopt">getopt</a>
                        -
                        <span data-more>Parse command-line options</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getopt_long">getopt_long</a>
                        -
                        <span data-more>Parse command-line options</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getopt_long_only">getopt_long_only</a>
                        -
                        <span data-more>Parse command-line options</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getpagesize">getpagesize</a>
                        -
                        <span data-more>get memory page size</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getpass">getpass</a>
                        -
                        <span data-more>get a password</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getresgid">getresgid</a>
                        -
                        <span data-more>get real, effective and saved user/group IDs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getresgid32">getresgid32</a>
                        -
                        <span data-more>get real, effective and saved user/group IDs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getresuid">getresuid</a>
                        -
                        <span data-more>get real, effective and saved user/group IDs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getresuid32">getresuid32</a>
                        -
                        <span data-more>get real, effective and saved user/group IDs</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/gettid">gettid</a>
                        -
                        <span data-more>get thread identification</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getuid">getuid</a>
                        -
                        <span data-more>get user identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/getuid32">getuid32</a>
                        -
                        <span data-more>get user identity</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getusershell">getusershell</a>
                        -
                        <span data-more>get permitted user shells</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getwd">getwd</a>
                        -
                        <span data-more>get current working directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/group_member">group_member</a>
                        -
                        <span data-more>test whether a process is in a group</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/idle">idle</a>
                        -
                        <span data-more>make process 0 idle</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/isatty">isatty</a>
                        -
                        <span data-more>test whether a file descriptor refers to a terminal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/lchown">lchown</a>
                        -
                        <span data-more>change ownership of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/lchown32">lchown32</a>
                        -
                        <span data-more>change ownership of a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/link">link</a>
                        -
                        <span data-more>make a new name for a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/linkat">linkat</a>
                        -
                        <span data-more>make a new name for a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/lockf">lockf</a>
                        -
                        <span data-more>apply, test or remove a POSIX lock on an open file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/mincore">mincore</a>
                        -
                        <span data-more>determine whether pages are resident in memory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/nice">nice</a>
                        -
                        <span data-more>change process priority</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/optarg">optarg</a>
                        -
                        <span data-more>Parse command-line options</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/opterr">opterr</a>
                        -
                        <span data-more>Parse command-line options</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/optind">optind</a>
                        -
                        <span data-more>Parse command-line options</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/optopt">optopt</a>
                        -
                        <span data-more>Parse command-line options</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/pathconf">pathconf</a>
                        -
                        <span data-more>get configuration values for files</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pause">pause</a>
                        -
                        <span data-more>wait for signal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pipe">pipe</a>
                        -
                        <span data-more>create pipe</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pipe2">pipe2</a>
                        -
                        <span data-more>create pipe</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pread">pread</a>
                        -
                        <span data-more>read from or write to a file descriptor at a given offset</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pread64">pread64</a>
                        -
                        <span data-more>read from or write to a file descriptor at a given offset</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/profil">profil</a>
                        -
                        <span data-more>execution time profile</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pwrite">pwrite</a>
                        -
                        <span data-more>read from or write to a file descriptor at a given offset</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/pwrite64">pwrite64</a>
                        -
                        <span data-more>read from or write to a file descriptor at a given offset</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/read">read</a>
                        -
                        <span data-more>read from a file descriptor</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/readlink">readlink</a>
                        -
                        <span data-more>read value of a symbolic link</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/readlinkat">readlinkat</a>
                        -
                        <span data-more>read value of a symbolic link</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/reboot">reboot</a>
                        -
                        <span data-more>reboot or enable/disable Ctrl-Alt-Del</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/rmdir">rmdir</a>
                        -
                        <span data-more>delete a directory</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sbrk">sbrk</a>
                        -
                        <span data-more>change data segment size</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setdomainname">setdomainname</a>
                        -
                        <span data-more>get/set NIS domain name</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sethostid">sethostid</a>
                        -
                        <span data-more>get or set the unique identifier of the current host</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sethostname">sethostname</a>
                        -
                        <span data-more>get/set hostname</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setkey">setkey</a>
                        -
                        <span data-more>encrypt 64-bit messages</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setkey_r">setkey_r</a>
                        -
                        <span data-more>encrypt 64-bit messages</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setresgid">setresgid</a>
                        -
                        <span data-more>set real, effective and saved user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setresgid32">setresgid32</a>
                        -
                        <span data-more>set real, effective and saved user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setresuid">setresuid</a>
                        -
                        <span data-more>set real, effective and saved user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setresuid32">setresuid32</a>
                        -
                        <span data-more>set real, effective and saved user or group ID</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/setup">setup</a>
                        -
                        <span data-more>setup devices and filesystems, mount root filesystem</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/setusershell">setusershell</a>
                        -
                        <span data-more>get permitted user shells</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sleep">sleep</a>
                        -
                        <span data-more>sleep for a specified number of seconds</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/swab">swab</a>
                        -
                        <span data-more>swap adjacent bytes</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/swapoff">swapoff</a>
                        -
                        <span data-more>start/stop swapping to file/device</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/swapon">swapon</a>
                        -
                        <span data-more>start/stop swapping to file/device</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/symlink">symlink</a>
                        -
                        <span data-more>make a new name for a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/symlinkat">symlinkat</a>
                        -
                        <span data-more>make a new name for a file</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sync">sync</a>
                        -
                        <span data-more>commit filesystem caches to disk</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/syncfs">syncfs</a>
                        -
                        <span data-more>commit filesystem caches to disk</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/syscall">syscall</a>
                        -
                        <span data-more>indirect system call</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/sysconf">sysconf</a>
                        -
                        <span data-more>get configuration information at run time</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/sysctl">sysctl</a>
                        -
                        <span data-more>read/write system parameters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tcgetpgrp">tcgetpgrp</a>
                        -
                        <span data-more>get and set terminal foreground process group</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/tcsetpgrp">tcsetpgrp</a>
                        -
                        <span data-more>get and set terminal foreground process group</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/truncate">truncate</a>
                        -
                        <span data-more>truncate a file to a specified length</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/truncate64">truncate64</a>
                        -
                        <span data-more>truncate a file to a specified length</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ttyname">ttyname</a>
                        -
                        <span data-more>return name of a terminal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ttyname_r">ttyname_r</a>
                        -
                        <span data-more>return name of a terminal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ualarm">ualarm</a>
                        -
                        <span data-more>schedule signal after given number of microseconds</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/unlink">unlink</a>
                        -
                        <span data-more>delete a name and possibly the file it refers to</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/unlinkat">unlinkat</a>
                        -
                        <span data-more>delete a name and possibly the file it refers to</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/uselib">uselib</a>
                        -
                        <span data-more>load shared library</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/usleep">usleep</a>
                        -
                        <span data-more>suspend execution for microsecond intervals</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/vhangup">vhangup</a>
                        -
                        <span data-more>virtually hangup the current terminal</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="2/write">write</a>
                        -
                        <span data-more>write to a file descriptor</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="utmpx.h">
            <a href="#utmpx.h">utmpx.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/getutmp">getutmp</a>
                        -
                        <span data-more>copy utmp structure to utmpx, and vice versa</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getutmpx">getutmpx</a>
                        -
                        <span data-more>copy utmp structure to utmpx, and vice versa</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="wchar.h">
            <a href="#wchar.h">wchar.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/btowc">btowc</a>
                        -
                        <span data-more>convert single byte to wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fgetws">fgetws</a>
                        -
                        <span data-more>read a wide-character string from a FILE stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fputws">fputws</a>
                        -
                        <span data-more>write a wide-character string to a FILE stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/fwide">fwide</a>
                        -
                        <span data-more>set and determine the orientation of a FILE stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/getwchar">getwchar</a>
                        -
                        <span data-more>read a wide character from standard input</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mbrlen">mbrlen</a>
                        -
                        <span data-more>determine number of bytes in next multibyte character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mbrtowc">mbrtowc</a>
                        -
                        <span data-more>convert a multibyte sequence to a wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mbsinit">mbsinit</a>
                        -
                        <span data-more>test for initial shift state</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mbsnrtowcs">mbsnrtowcs</a>
                        -
                        <span data-more>convert a multibyte string to a wide-character string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/mbsrtowcs">mbsrtowcs</a>
                        -
                        <span data-more>convert a multibyte string to a wide-character string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/putwchar">putwchar</a>
                        -
                        <span data-more>write a wide character to standard output</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/ungetwc">ungetwc</a>
                        -
                        <span data-more>push back a wide character onto a FILE stream</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcpcpy">wcpcpy</a>
                        -
                        <span data-more>copy a wide-character string, returning a pointer to i...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcpncpy">wcpncpy</a>
                        -
                        <span data-more>copy a fixed-size string of wide characters, returning...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcrtomb">wcrtomb</a>
                        -
                        <span data-more>convert a wide character to a multibyte sequence</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcscasecmp">wcscasecmp</a>
                        -
                        <span data-more>compare two wide-character strings, ignoring case</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcscat">wcscat</a>
                        -
                        <span data-more>concatenate two wide-character strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcschr">wcschr</a>
                        -
                        <span data-more>search a wide character in a wide-character string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcscmp">wcscmp</a>
                        -
                        <span data-more>compare two wide-character strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcscpy">wcscpy</a>
                        -
                        <span data-more>copy a wide-character string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcscspn">wcscspn</a>
                        -
                        <span data-more>search a wide-character string for any of a set of wid...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsdup">wcsdup</a>
                        -
                        <span data-more>duplicate a wide-character string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcslen">wcslen</a>
                        -
                        <span data-more>determine the length of a wide-character string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsncasecmp">wcsncasecmp</a>
                        -
                        <span data-more>compare two fixed-size wide-character strings, ignorin...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsncat">wcsncat</a>
                        -
                        <span data-more>concatenate two wide-character strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsncmp">wcsncmp</a>
                        -
                        <span data-more>compare two fixed-size wide-character strings</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsncpy">wcsncpy</a>
                        -
                        <span data-more>copy a fixed-size string of wide characters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsnlen">wcsnlen</a>
                        -
                        <span data-more>determine the length of a fixed-size wide-character st...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsnrtombs">wcsnrtombs</a>
                        -
                        <span data-more>convert a wide-character string to a multibyte string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcspbrk">wcspbrk</a>
                        -
                        <span data-more>search a wide-character string for any of a set of wid...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsrchr">wcsrchr</a>
                        -
                        <span data-more>search a wide character in a wide-character string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsrtombs">wcsrtombs</a>
                        -
                        <span data-more>convert a wide-character string to a multibyte string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsspn">wcsspn</a>
                        -
                        <span data-more>advance in a wide-character string, skipping any of a ...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcsstr">wcsstr</a>
                        -
                        <span data-more>locate a substring in a wide-character string</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcstok">wcstok</a>
                        -
                        <span data-more>split wide-character string into tokens</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcswidth">wcswidth</a>
                        -
                        <span data-more>determine columns needed for a fixed-size wide-charact...</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wctob">wctob</a>
                        -
                        <span data-more>try to represent a wide character as a single byte</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wcwidth">wcwidth</a>
                        -
                        <span data-more>determine columns needed for a wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wmemchr">wmemchr</a>
                        -
                        <span data-more>search a wide character in a wide-character array</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wmemcmp">wmemcmp</a>
                        -
                        <span data-more>compare two arrays of wide-characters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wmemcpy">wmemcpy</a>
                        -
                        <span data-more>copy an array of wide-characters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wmemmove">wmemmove</a>
                        -
                        <span data-more>copy an array of wide-characters</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wmemset">wmemset</a>
                        -
                        <span data-more>fill an array of wide-characters with a constant wide ...</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="wctype.h">
            <a href="#wctype.h">wctype.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/iswalnum">iswalnum</a>
                        -
                        <span data-more>test for alphanumeric wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswalpha">iswalpha</a>
                        -
                        <span data-more>test for alphabetic wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswblank">iswblank</a>
                        -
                        <span data-more>test for whitespace wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswcntrl">iswcntrl</a>
                        -
                        <span data-more>test for control wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswctype">iswctype</a>
                        -
                        <span data-more>wide-character classification</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswdigit">iswdigit</a>
                        -
                        <span data-more>test for decimal digit wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswgraph">iswgraph</a>
                        -
                        <span data-more>test for graphic wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswlower">iswlower</a>
                        -
                        <span data-more>test for lowercase wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswprint">iswprint</a>
                        -
                        <span data-more>test for printing wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswpunct">iswpunct</a>
                        -
                        <span data-more>test for punctuation or symbolic wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswspace">iswspace</a>
                        -
                        <span data-more>test for whitespace wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswupper">iswupper</a>
                        -
                        <span data-more>test for uppercase wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/iswxdigit">iswxdigit</a>
                        -
                        <span data-more>test for hexadecimal digit wide character</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/towctrans">towctrans</a>
                        -
                        <span data-more>wide-character transliteration</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/towlower">towlower</a>
                        -
                        <span data-more>convert a wide character to lowercase</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/towlower_l">towlower_l</a>
                        -
                        <span data-more>convert a wide character to lowercase</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/towupper">towupper</a>
                        -
                        <span data-more>convert a wide character to uppercase</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/towupper_l">towupper_l</a>
                        -
                        <span data-more>convert a wide character to uppercase</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wctrans">wctrans</a>
                        -
                        <span data-more>wide-character translation mapping</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wctype">wctype</a>
                        -
                        <span data-more>wide-character classification</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    

        <h1 id="wordexp.h">
            <a href="#wordexp.h">wordexp.h</a>
        </h1>

        <ul>

            
            
                

                    

                    <li>
                        <a href="3/wordexp">wordexp</a>
                        -
                        <span data-more>perform word expansion like a posix-shell</span>
                        <span data-less></span>
                    </li>

                

            
            
                

                    

                    <li>
                        <a href="3/wordfree">wordfree</a>
                        -
                        <span data-more>perform word expansion like a posix-shell</span>
                        <span data-less></span>
                    </li>

                

            

        </ul>

    


        </div>

    </body>

</html>