function adjustTextareaHeight() {
    textarea.style.height = 'auto';
    const scrollHeight = textarea.scrollHeight;
    textarea.style.height = Math.min(scrollHeight, 600) + 'px';
    console.log("adjust!");
}
// 輸入框按下之後顯示對話
function openModal() {
    // 顯示 modal
    var modal = new bootstrap.Modal(document.getElementById('editbioModal'));
    modal.show();
}
document.addEventListener('DOMContentLoaded', function () {
    // 輸入框高度自適應
    const textarea = document.getElementById('articleContent');
    if (textarea) {
        textarea.addEventListener('input', adjustTextareaHeight);
    }
    else console.log("can't find articleContent");
    // 簡介區塊點擊後顯示對話框 (textarea)
    var bio = document.getElementById('bio');
    if (bio) {
        // 加入() = 觸發一次
        bio.onclick = openModal;
    }
    else console.log("can't find intro");
});
// 新增驗證方法
// $.validator.addMethod("notEqualTo", function (value, element, param) {
//     return this.optional(element) || value != $(param).val();
// }, "新密碼不能與舊密碼相同");
// 從資料庫讀取很麻煩, 擱置
$(document).ready(function () {
    //自定義驗證方法
    $.validator.addMethod("pattern", function (value, element, param) {
        return this.optional(element) || param.test(value);
    }, "格式不正確");
    var validateProfile = function () {
        $("#EditProfile").validate({
            onfocusout: false,
            onkeyup: false,
            onclick: false,
            rules: {
                username: {
                    required: true,
                    minlength: 4,
                    maxlength: 16,
                    pattern: /^[a-zA-Z0-9]+$/
                },
                penName:
                {
                    required: true,
                    maxlength: 10
                },
                newpassword: {
                    required: false,
                    minlength: 6,
                    maxlength: 16
                },
                email: {
                    required: true,
                    email: true
                },
                phone: {
                    required: true,
                    digits: true,
                    minlength: 10,
                    maxlength: 10
                }
            },
            messages: {
                username: {
                    required: "請輸入使用者名稱",
                    minlength: "使用者名稱至少要4個字元",
                    maxlength: "使用者名稱最多16個字元",
                    pattern: "使用者名稱只能包含英文和數字"
                },
                penName:
                {
                    required: "請輸入筆名",
                    maxlength: "筆名最多16個字元"
                },
                newpassword: {
                    required: "請輸入密碼",
                    minlength: "密碼至少要6個字元",
                    maxlength: "密碼最多16個字元"
                },
                email: {
                    required: "請輸入電子郵件",
                    email: "請輸入正確的電子郵件"
                },
                phone: {
                    required: "請輸入手機號碼",
                    digits: "手機號碼為數字",
                    minlength: "手機號碼為10個數字",
                    maxlength: "手機號碼為10個數字"
                }
            },
            errorPlacement: function (error, element) {
                var errorId = element.attr("id") + "-err";
                $('#' + errorId).html(error.text()); // 顯示錯誤訊息到<p>當中
            },
            success: function (label, element) {
                var successId = $(element).attr("id") + "-err";
                $('#' + successId).html("");// 正確就清掉 (如果原先是錯的)
            }
        });
    };
    $('#EditConfirm').click(function (event) {
        event.preventDefault();
        validateProfile(); // 觸發表單驗證
        if ($("#EditProfile").valid()) { // 如果表單驗證通過，則提交表單
            console.log("validate!");
            $("#EditProfile").submit();
        }
        else console.log("validate Fail!");
    });
});