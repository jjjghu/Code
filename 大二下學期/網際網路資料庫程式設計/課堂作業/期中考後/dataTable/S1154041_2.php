<!DOCTYPE html>
<html>

<head>
    <meta charset="utf-8">
    <title></title>
    <link href="//maxcdn.bootstrapcdn.com/bootstrap/3.3.7/css/bootstrap.min.css" rel="stylesheet">
    <link href="//cdn.datatables.net/1.10.16/css/dataTables.bootstrap.min.css" rel="stylesheet">
    <link href="//cdnjs.cloudflare.com/ajax/libs/toastr.js/2.1.4/toastr.min.css" rel="stylesheet">

    <script src="//code.jquery.com/jquery-3.3.1.js"></script>
    <script src="//cdn.datatables.net/1.10.16/js/jquery.dataTables.min.js"></script>
    <script src="//cdn.datatables.net/1.10.16/js/dataTables.bootstrap.min.js"></script>
    <script src="//ajax.aspnetcdn.com/ajax/jquery.validate/1.14.0/jquery.validate.min.js"></script>
    <script src="//ajax.aspnetcdn.com/ajax/jquery.validate/1.11.1/localization/messages_zh_TW.js"></script>
    <script src="//cdnjs.cloudflare.com/ajax/libs/toastr.js/2.1.4/toastr.min.js"></script>
    <script src="datatable2.js"></script>
    <style>
        body {
            font-family: "微軟正黑體";
        }

        .error {
            color: #D82424;
            font-weight: normal;
            display: inline;
            padding: 1px;
        }
    </style>
</head>

<body>
    <div class="row">
        <div class="col-md-2"></div>
        <div class="col-md-8 text-center">
            <form class="form-horizontal form-inline" name="form1" id="form1" method="post">
                <input type="hidden" name="oper" id="oper" value="insert">
                <input type="hidden" name="stud_no_old" id="stud_no_old" value="">
                <table id="edit" class="table table-striped table-bordered">
                    <thead>
                        <tr>
                            <th class="text-center">學號</th>
                            <th class="text-center">姓名</th>
                            <th class="text-center">性別</th>
                            <th class="text-center">地址</th>
                            <th class="text-center">存檔/取消</th>
                        </tr>
                        <tr>
                            <td class="text-center">
                                <input type="text" id="stud_no" name="stud_no">
                            </td>
                            <td class="text-center">
                                <input type="text" id="stud_name" name="stud_name">
                            </td>
                            <td class="text-center">
                                <input type="radio" id="stud_sex" name="stud_sex" value='M'> 男
                                <input type="radio" id="stud_sex" name="stud_sex" value='F'> 女
                            </td>
                            <td class="text-center">
                                <input type="text" id="stud_addr" name="stud_addr">
                            </td>
                            <td>
                                <button type="submit" class="btn btn-primary btn-xs" id="btn-save"><i
                                        class="glyphicon glyphicon-save"></i>存檔</button>
                                <button type="reset" class="btn btn-danger btn-xs" id="btn-cancel">取消</button>
                            </td>
                        </tr>
                    </thead>
                </table>
                <table id="example" class="table table-striped table-bordered">
                    <thead>
                        <tr>
                            <th class="text-center">學號</th>
                            <th class="text-center">姓名</th>
                            <th class="text-center">性別</th>
                            <th class="text-center">地址</th>
                            <th class="text-center">修改/刪除</th>
                        </tr>
                    </thead>
                </table>
        </div>
        <div class="col-md-2"></div>
    </div>
</body>

</html>