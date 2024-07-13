<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>正規表達式</title>
    <style>
        .result {
            color: red;
        }

        .result.valid {
            color: blue;
        }

        .result.invalid {
            color: red;
        }
    </style>
</head>

<body>
    <label>請輸入身份證字號:</label>
    <input type="text" id="enter">
    <button onclick="validateID()">送出資料</button>
    <br>
    <label id="result" class="result"></label>

    <script>
        function validateID() {
            const enter = document.getElementById('enter').value;
            const resultLabel = document.getElementById('result');
            const rule = /^[A-Z][12]\d{8}$/;

            if (rule.test(enter)) {
                resultLabel.textContent = `${enter} 是正確的身份證字號格式`;
                resultLabel.classList.remove('invalid');
                resultLabel.classList.add('valid');
            } else {
                resultLabel.textContent = `${enter} 是錯誤的身份證字號格式`;
                resultLabel.classList.remove('valid');
                resultLabel.classList.add('invalid');
            }
        }
    </script>
</body>

</html>