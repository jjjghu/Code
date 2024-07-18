<!DOCTYPE html>
<html class=" idc0_343 mnsmaop"><grammarly-extension data-grammarly-shadow-root="true"
    style="position: absolute; top: 0px; left: 0px; pointer-events: none;"
    class="dnXmp"></grammarly-extension><grammarly-extension data-grammarly-shadow-root="true"
    style="position: absolute; top: 0px; left: 0px; pointer-events: none;" class="dnXmp"></grammarly-extension>

<head>
    <meta charset="UTF-8">
    <title> 公告張貼 </title>
    <script src="//ajax.googleapis.com/ajax/libs/jquery/1.12.0/jquery.min.js"></script>
    <script src="//ajax.aspnetcdn.com/ajax/jquery.validate/1.14.0/jquery.validate.min.js"></script>
    <script src="//ajax.aspnetcdn.com/ajax/jquery.validate/1.11.1/localization/messages_zh_TW.js "></script>
    <script src="//jqueryvalidation.org/files/dist/additional-methods.min.js"></script>
    <link href="post_style.css" rel="stylesheet" type="text/css">
    <style type="text/css">
        .error {
            color: red;
            font-weight: normal;
        }

        table {
            margin: 0 auto;
        }
    </style>
    <!-- <style>
        body {
            background-color: #F7F7F7;
        }

        .c_title {
            background-color: #E6E6E6;
            margin-top: 3px;
            padding-top: 5px;
            padding-bottom: 3px;
            padding-left: 5px;
            font-size: 11pt;
            color: #990033;
        }

        .c_content {
            background-color: #FFFFFF;
            margin-top: 3px;
            padding-top: 5px;
            padding-bottom: 3px;
            padding-left: 5px;
            font-size: 11pt;
            color: blue;
        }

        .c_button {
            background: #e3e3db;
            font-size: 16px;
            color: #6633FF;
            padding: 6px 14px;
            border-width: 2px;
            border-style: solid;
            border-color: #fff #d8d8d0 #d8d8d0 #fff;
            text-decoration: none;
            text-transform: uppercase;
            font-weight: bold;
        }
    </style> -->
</head>

<body data-new-gr-c-s-check-loaded="14.1064.0" data-gr-ext-installed="" data-new-gr-c-s-loaded="14.1064.0">
    <form name="form1" id="form1" action="" method="POST" novalidate="novalidate">
        <table>
            <tbody>
                <tr>
                    <td class="c_title" width="110">公告對象：</td>
                    <td class="c_content" width="420">
                        <input type="checkbox" class="to_group error" name="to_1" aria-invalid="true">
                        <label id="to_1-error" class="error" for="to_1"></label>教職員
                        <input type="checkbox" class="to_group error" name="to_2" aria-invalid="true">
                        <label id="to_2-error" class="error" for="to_2"></label>學生
                        <input type="checkbox" class="to_group error" name="to_3" aria-invalid="true">學校首頁

                        <!-- 若php POST接受到沒有勾選, 顯示錯誤訊息 -->
                        <?php
                        if (empty($_POST['to_1']) && empty($_POST['to_2']) && empty($_POST['to_3'])) {
                            echo '<label for="to_3" class="error">請至少選擇1項</label>';
                        }
                        ?>
                    </td>
                </tr>
                <tr>
                    <td class="c_title">公告類型：</td>
                    <td class="c_content">
                        <input type="radio" name="type" value="1" aria-required="true" class="error">演講
                        <input type="radio" name="type" value="2" class="error">研討會
                        <input type="radio" name="type" value="3" class="error">徵才
                        <input type="radio" name="type" value="4" class="error">招生、進修教育訓練
                        <input type="radio" name="type" value="5" class="error">其他
                        <!-- 若沒有選擇, 跳出錯誤訊息 -->
                        <?php
                        if (empty($_POST['type']))
                            echo '<label for="type" class="error">必填</label>';
                        ?>
                    </td>
                </tr>
                <tr>
                    <td class="c_title">主旨：</td>
                    <td class="c_content">
                        <input type="text" name="abstract" size="30" maxlength="30" value="" aria-required="true"
                            class="error"><label id="abstract-error" class="error" for="abstract">
                            <?php
                            if (empty($_POST['abstract']))
                                echo '必填';
                            ?>
                        </label>
                    </td>

                </tr>
                <tr>
                    <td class="c_title">公告截止日期：</td>
                    <td class="c_content">
                        <select name="year">
                            <option value="101">101</option>
                            <option value="102">102</option>
                            <option value="103">103</option>
                            <option value="104">104</option>
                            <option value="105">105</option>
                            <option value="106">106</option>
                            <option value="107">107</option>
                            <option value="108">108</option>
                            <option value="109">109</option>
                            <option value="110">110</option>
                            <option value="111">111</option>
                            <option value="112">112</option>
                            <option value="113" selected="">113</option>
                            <option value="114">114</option>
                            <option value="115">115</option>
                            <option value="116">116</option>
                            <option value="117">117</option>
                            <option value="118">118</option>
                            <option value="119">119</option>
                            <option value="120">120</option>
                            <option value="121">121</option>
                            <option value="122">122</option>
                            <option value="123">123</option>
                            <option value="124">124</option>
                            <option value="125">125</option>
                            <option value="126">126</option>
                            <option value="127">127</option>
                            <option value="128">128</option>
                            <option value="129">129</option>
                            <option value="130">130</option>
                        </select>年
                        <select name="month">
                            <option value="1">1</option>
                            <option value="2">2</option>
                            <option value="3">3</option>
                            <option value="4" selected="">4</option>
                            <option value="5">5</option>
                            <option value="6">6</option>
                            <option value="7">7</option>
                            <option value="8">8</option>
                            <option value="9">9</option>
                            <option value="10">10</option>
                            <option value="11">11</option>
                            <option value="12">12</option>
                        </select>月
                        <select name="day">
                            <option value="1">1</option>
                            <option value="2">2</option>
                            <option value="3">3</option>
                            <option value="4">4</option>
                            <option value="5">5</option>
                            <option value="6">6</option>
                            <option value="7">7</option>
                            <option value="8">8</option>
                            <option value="9">9</option>
                            <option value="10">10</option>
                            <option value="11">11</option>
                            <option value="12">12</option>
                            <option value="13">13</option>
                            <option value="14">14</option>
                            <option value="15">15</option>
                            <option value="16">16</option>
                            <option value="17">17</option>
                            <option value="18">18</option>
                            <option value="19">19</option>
                            <option value="20">20</option>
                            <option value="21">21</option>
                            <option value="22">22</option>
                            <option value="23" selected="">23</option>
                            <option value="24">24</option>
                            <option value="25">25</option>
                            <option value="26">26</option>
                            <option value="27">27</option>
                            <option value="28">28</option>
                            <option value="29">29</option>
                            <option value="30">30</option>
                            <option value="31">31</option>
                        </select>日
                    </td>
                </tr>
                <tr>
                    <td class="c_title">連接網址：</td>
                    <td class="c_content">
                        <input type="text" name="link" size="20" value="" aria-required="true" class="error"
                            aria-invalid="true"><label id="link-error" class="error" for="link">
                            <?php
                            // 驗證網址
                            if (empty($_POST['link']) || !filter_var($_POST['link'], FILTER_VALIDATE_URL))
                                echo '請輸入合法的URL';
                            ?>
                        </label>
                    </td>
                </tr>
                <tr>
                    <td class="c_title">公告內容：</td>
                    <td class="c_content">
                        <textarea name="content" rows="5" cols="40" aria-required="true" class="error"
                            spellcheck="false" aria-invalid="true"></textarea><label id="content-error" class="error"
                            for="content">
                            <?php
                            if (empty($_POST['content']))
                                echo '必填';
                            ?>
                        </label>
                    </td>
                </tr>
                <tr>
                    <td colspan="2" align="center">
                        <button type="submit" class="c_button">確定送出</button>
                        <button type="reset" class="c_button">重新填寫</button>
                    </td>
                </tr>
            </tbody>
        </table>
    </form>
    <?php
    // 獲取輸入的 POST 若無則空字串
    $to_1 = isset($_POST['to_1']) ? "教職員" : '';
    $to_2 = isset($_POST['to_2']) ? "學生" : '';
    $to_3 = isset($_POST['to_3']) ? "學校首頁" : '';
    $type_array = array(1 => "演講", "研討會", "徵才", "招生、進修教育訓練", "其他");
    $type = isset($_POST['type']) ? $type_array[$_POST['type']] : '';
    $abstract = isset($_POST['abstract']) ? $_POST['abstract'] : '';
    $year = $_POST['year'];
    $month = $_POST['month'];
    $day = $_POST['day'];
    $link = isset($_POST['link']) ? $_POST['link'] : '';
    $content = isset($_POST['content']) ? $_POST['content'] : '';
    // 顯示表單內容
    echo '
        <table>
            <tbody>
                <tr>
                    <td class="c_title" width="110">公告對象：</td>
                    <td class="c_content" width="420">' . implode(' ', [$to_1, $to_2, $to_3]) . '</td>
                    
                </tr>
                <tr>
                    <td class="c_title">公告類型：</td>
                    <td class="c_content">' . $type . '</td>
                </tr>
                <tr>
                    <td class="c_title">主旨：</td>
                    <td class="c_content">' . $abstract . '</td>
                </tr>
                <tr>
                    <td class="c_title">公告截止日期：</td>
                    <td class="c_content">' . $year . '年' . $month . '月' . $day . '日</td>
                </tr>
                <tr>
                    <td class="c_title">連接網址：</td>
                    <td>' . $link . '</td>
                </tr>
                <tr>
                    <td class="c_title">公告內容：</td>
                    <td>' . $content . '</td>
            </tbody>
        </table>';
    ?>
    <!-- <script>
        $(document).ready(function ($) {
            $("#form1").validate({
                submitHandler: function (form) {
                    form.submit();
                },
                rules: {
                    to_1: {
                        require_from_group: [1, ".to_group"]
                    },
                    to_2: {
                        require_from_group: [1, ".to_group"]
                    },
                    to_3: {
                        require_from_group: [1, ".to_group"]
                    },
                    type: {
                        required: true
                    },
                    abstract: {
                        required: true
                    },
                    link: {
                        required: true,
                        url: true
                    },
                    content: {
                        required: true
                    },
                },
                messages: {
                    to_1: {
                        require_from_group: ""
                    },
                    to_2: {
                        require_from_group: ""
                    },
                    to_3: {
                        require_from_group: "請至少選擇1項"
                    }

                }
            });
        });
    </script> -->

</body><grammarly-desktop-integration
    data-grammarly-shadow-root="true"></grammarly-desktop-integration><grammarly-mirror
    data-grammarly-shadow-root="true" class="dnXmp"></grammarly-mirror><grammarly-popups
    data-grammarly-shadow-root="true" class="dnXmp"></grammarly-popups>

</html>