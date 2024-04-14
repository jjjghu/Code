$(document).ready(function () {
    // 添加按鈕的功能
    $('#add').click(function (e) {
        // 避免刷新網頁
        e.preventDefault();
        // 若已經添加過, 就不能再加入
        // console.log($('#dataTable tr').length);
        if ($('#dataTable tr').length > 2) {
            return;
        }
        // 加入新的表單到dataTable後面
        $('#dataTable').append(`
            <tr>
                <td class="form-number"><button class='btn btn-danger' id="removeRowButton">移除</button>2</td>
                <td class="form-normal"><input type="text" class="form-control" name="enter6" id="enter6""><span id='enter6Err'></span></td>
                <td class="form-normal"><input type="text" class="form-control" name="enter7" id="enter7""><span id='enter7Err'></span></td>
                <td class="form-normal"><input type="text" class="form-control" name="enter8" id="enter8""><span id='enter8Err'></span></td>
                <td class="form-email"><input type="text" class="form-control " name="enter9" id="enter9""><span id='enter9Err'></span></td>
            </tr>
        `);
    });
    // 刪除按鈕, 會刪掉距離最近的tr網頁物件
    $(document).on('click', '#removeRowButton', function () {
        $(this).closest('tr').remove();
    });
    // 表單驗證開始
    $("#form1").validate({
        // 制定規則
        rules: {
            enter1: "required",
            enter2: "required",
            enter3: "required",
            enter4: "required",
            enter5: { required: true, email: true },
            enter6: "required",
            enter7: "required",
            enter8: "required",
            enter9: { required: true, email: true }
        },
        // 對應的錯誤訊息
        messages: {
            enter1: "必須填寫",
            enter2: "必須填寫",
            enter3: "必須填寫",
            enter4: "必須填寫",
            enter5: "請輸入有效的電子郵件",
            enter6: "必須填寫",
            enter7: "必須填寫",
            enter8: "必須填寫",
            enter9: "請輸入有效的電子郵件"
        },
        // 將錯誤訊息放在指定的位置
        errorPlacement: function (error, element) {
            // 發生錯誤的位置id為 enter+數字
            var id = $(element).attr('id') + 'Err'; // 對應的錯誤訊息元素的ID
            // 放置錯誤的位置id 為 enter+數字+Err
            error.appendTo($('#' + id));
        }
    });
    // 表單驗證結束
});
