<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <title></title>
    <link href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
    <link href="//cdn.datatables.net/1.10.16/css/dataTables.bootstrap.min.css" rel="stylesheet">
    <script src="//code.jquery.com/jquery-3.3.1.js"></script>
    <script src="//cdn.datatables.net/1.10.16/js/jquery.dataTables.min.js"></script>
    <script src="//cdn.datatables.net/1.10.16/js/dataTables.bootstrap.min.js"></script>
    <script>
        $(function () {
            $('#UserTable').DataTable({
                "ajax": 'datatable1_ajax.php'
            });
        });
    </script>
</head>

<body>
    <div class="row">
        <div class="col-md-3"></div>
        <div class="col-md-6 text-center">
            <table id="UserTable" class="table table-striped table-bordered">
                <thead>
                    <tr>
                        <th class="text-center">id</th>
                        <th class="text-center">使用者名稱</th>
                        <th class="text-center">手機號碼</th>
                        <th class="text-center">電子郵件</th>
                    </tr>
                </thead>
            </table>
        </div>
        <div class="col-md-3"></div>
    </div>

</body>

</html>