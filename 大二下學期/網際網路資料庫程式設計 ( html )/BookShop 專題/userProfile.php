<!-- 沒有登入 -> 跳轉到登入頁面 -->
<?php
if (session_status() == PHP_SESSION_NONE) {
    session_start();
}
if (!isset($_SESSION['username'])) {
    header("Location: login.php");
    exit();
}
?>
<!DOCTYPE html>
<html lang="zh-Hant-TW">

<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>個人資料</title>
    <link href="bootstrap-5.3.2-dist/css/bootstrap.min.css" rel="stylesheet">
    <?php include '.Style.php' ?>

</head>
<?php include '.Theme.php'; ?>
<?php include '.LinkSql.php';
// 找到使用者 id, 獲取資料
$check_sql = "SELECT username, bio, phone, email, penName FROM author WHERE id = ?";
$stmt = $link->prepare($check_sql);
$stmt->bind_param("s", $_SESSION['user_id']);
$stmt->execute();
$stmt->store_result();
if ($stmt->num_rows == 1) {
    //獲取個人資訊
    $stmt->bind_result($username, $bio, $phone, $email, $penName);
    $stmt->fetch();
}
?>

<body class=<?php echo $theme ?>>
    <!-- 標題橫條 + 切換按鈕 -->
    <?php include '.Header.php'; ?>
    <!-- 主要頁面內容開始 -->
    <main class="container mt-10vh">
        <div class="row">
            <!-- 個人資料區塊開始 -->
            <div class="col-md-4">
                <div class="profile-header">
                    <div class="profile-info d-flex flex-column align-items-center mb-5">
                        <div class="d-flex">
                            <h2 class="h4">
                                <!-- 使用 session, 而不是搜尋結果 -->
                                <?php echo (isset($_SESSION['penName'])) ? $_SESSION['penName'] : $_SESSION['username']; ?>
                            </h2>
                            <button type="button" id="editProfile" class="bi bi-pencil-fill ms-1 btn-small-icon"
                                data-bs-toggle="modal" data-bs-target="#editProfileModal"></button>
                        </div>
                        <!-- 訊息, 顯示是否更新成功 -->
                        <?php if (isset($_SESSION['message'])): ?>
                            <script>
                                alert(<?php echo json_encode($_SESSION['message']); ?>);
                            </script>
                            <?php unset($_SESSION['message']); ?>
                        <?php endif; ?>
                    </div>
                </div>
                <div class="mb-3">
                    <!-- 簡介區塊 -->
                    <textarea class="form-control" rows="10" id="bio"
                        placeholder="<?php echo ($bio == "") ? '暫無簡介' : "$bio"; ?>" readonly></textarea>
                </div>
                <div class="d-flex">
                    <h3>動態<h3>
                </div>
                <div class="scroll-box">
                    <ul>
                        <li>剛剛發布的新的文章「漫步野花中的吹笛手」</li>
                        <li>一天前發布了新的文章「一瞬時刻」</li>
                        <li>兩天前發布了新的文章「我打江南走過」</li>
                        <li>七天前發布了新的文章「我欲乘風歸去」</li>
                    </ul>
                </div>
            </div>
            <div class="col-md-8">
                <h3>文章撰寫</h3>
                <div class="row">
                    <div class="col-md-3">
                        <div data-bs-toggle='modal' data-bs-target='#editArticleModal'
                            class='edit text-decoration-none text-primary'>
                            <div class='card d-flex align-items-center justify-content-center'>
                                <i class="bi bi-file-earmark-plus"></i>
                                <h5 id="new-article" class='card-title text-Nmain clamp-lines mb-auto'>
                                    撰寫新文章
                                </h5>
                            </div>
                        </div>
                    </div>
                    <div class="col-md-3">
                        <!-- 跳轉文章編輯 -->
                        <div data-bs-toggle='modal' data-bs-target='#EditArticle'
                            class='edit text-decoration-none text-primary'>
                            <div class='card mb-3 d-flex flex-column'>
                                <img src='<?php echo $product["image"]; ?>' class='card-img-top' alt='Product Image'>
                                <div class='card-body d-flex flex-column'>
                                    <h5 class='card-title text-Nmain clamp-lines mb-auto'>
                                        <?php echo htmlspecialchars($product["name"]); ?>
                                    </h5>
                                    <button class='btn cart' aria-label='編輯圖示'>編輯</button>
                                    <p class='card-text fw-bold text-orange mt-auto'><?php echo $product["price"]; ?>
                                    </p>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>
            <!-- 個人資料編輯區Modal -->
            <div class="modal fade" id="editProfileModal" tabindex="-1" aria-labelledby="editProfileModalLabel"
                aria-hidden="true">
                <div class="modal-dialog modal-dialog-centered">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h5 class="modal-title" id="editProfileModalLabel">編輯個人資料</h5>
                        </div>
                        <div class="modal-body">
                            <form id="EditProfile" action=".EditProfile.php" method="post">
                                <div class="mb-3">
                                    <input type="text" class="form-control" id="username" name="username"
                                        placeholder="使用者名稱" value="<?php echo $username; ?>">

                                    <p class="text-red" id="username-err"></p>
                                </div>
                                <div class="mb-3">
                                    <input type="text" class="form-control" id="penName" name="penName" placeholder="筆名"
                                        value="<?php echo $penName; ?>">
                                    <p class="text-red" id="penName-err"></p>
                                </div>
                                <div class="mb-3">
                                    <input type="password" class="form-control" id="newpassword" name="newpassword"
                                        placeholder="新密碼">
                                    <p class="text-red" id="newpassword-err"></p>
                                </div>
                                <div class="mb-3">
                                    <input type="email" class="form-control" id="email" name="email" placeholder="電子信箱"
                                        value="<?php echo $email; ?>">
                                    <p class="text-red" id="email-err"></p>
                                </div>
                                <div class="mb-3">
                                    <input type="tel" class="form-control" id="phone" name="phone" placeholder="手機號碼"
                                        value="<?php echo $phone; ?>">
                                    <p class="text-red" id="phone-err"></p>
                                </div>
                                <div class="d-flex justify-content-end">
                                    <div>
                                        <button type="button" class="btn btn-secondary me-2"
                                            data-bs-dismiss="modal">取消</button>
                                        <button type="submit" id="EditConfirm" class="btn btn-primary">保存變更</button>
                                    </div>
                                </div>
                            </form>
                        </div>
                    </div>
                </div>
            </div>
            <!-- 個人簡介 Modal -->
            <div class="modal fade" id="editbioModal" tabindex="-1" aria-labelledby="editbioModalLabel"
                aria-hidden="true">
                <div class="modal-dialog modal-dialog-centered">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h5 class="modal-title" id="editProfileModalLabel">編輯簡介</h5>
                        </div>
                        <div class="modal-body">
                            <form id="Editbio" action=".EditBio.php" method="post">
                                <div class="mb-3">
                                    <textarea id="bioTextarea" class="form-control" name="bio"
                                        rows="15"><?php echo $bio; ?></textarea>
                                </div>
                                <div class="d-flex justify-content-end">
                                    <button type="button" class="btn btn-secondary me-2"
                                        data-bs-dismiss="modal">取消</button>
                                    <button type="submit" class="btn btn-primary">保存變更</button>
                                </div>
                            </form>
                        </div>
                    </div>
                </div>
            </div>
            <!-- 撰寫新文章Modal -->
            <!-- <div class="modal fade" id="editArticleModal" tabindex="-1" aria-labelledby="editArticleModalLabel"
                aria-hidden="true">
                <div class="modal-dialog modal-dialog-centered modal-xl">
                    <div class="modal-content">
                        <div class="modal-header">
                            <h5 class="modal-title" id="editArticleModalLabel">編輯文章</h5>
                        </div>
                        <div class="modal-body">
                            <form>
                                <div class="mb-3">
                                    <input type="text" class="form-control" id="articleTitle" placeholder="輸入標題">
                                </div>
                                <div class="mb-3">
                                    <textarea class="form-control " id="articleContent" rows="20"
                                        placeholder="輸入內容"></textarea>
                                </div>
                                <div class="d-flex justify-content-end">
                                    <div>
                                        <button type="button" class="btn btn-secondary me-2"
                                            data-bs-dismiss="modal">取消</button>
                                        <button type="submit" class="btn btn-primary">保存變更</button>
                                    </div>
                                </div>
                            </form>
                        </div>
                    </div>
                </div> -->
        </div>
        <?php include '.EditArticle.php'; ?>
        </div>
    </main>
    <!-- 主要頁面內容結束 -->
    <?php include '.Footer.php'; ?>
    <?php include '.Script.php' ?>

</body>

</html>