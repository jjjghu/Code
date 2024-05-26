document.addEventListener('DOMContentLoaded', () => {
    // 黑暗模式切換按鈕, 都在Loaded之後確認按紐存在, 再加入功能
    var themeIcon = document.getElementById('themeIcon');
    if (themeIcon) {
        themeIcon.onclick = function () {
            document.body.classList.toggle('dark-theme');
            themeIcon.classList.toggle('bx-brightness');
            themeIcon.classList.toggle('bx-moon');
            // 用 js 將 cookie 存放在瀏覽器中
            if (document.body.classList.contains('dark-theme')) {
                document.cookie = "theme=dark-theme; path=/";
            } else {
                document.cookie = "theme=none; path=/";
            }
        }
    }
    // 顯示購物車頁面的按鈕
    var toggleCart = document.getElementById('toggleCart');
    if (toggleCart) {
        toggleCart.onclick = function () {
            var cartPreview = document.getElementById('cart-preview');
            // 將 cart-preview 當中的 display 設定為 flex
            if (cartPreview) {
                cartPreview.style.display = cartPreview.style.display === 'flex' ? 'none' : 'flex';
            }
        }
    }
});
// 增加購物車數量
function PlusCartCount() {
    var cartCount = document.getElementById('cart-count');
    if (cartCount.textContent == 0) {
        cartCount.style.display = 'block';
    }
    ++cartCount.textContent;
}
// 減少購物車數量
function MinusCartCount() {
    var cartCount = document.getElementById('cart-count');
    if (cartCount.textContent > 0) {
        --cartCount.textContent;
    }
    if (cartCount.textContent <= 1) {
        cartCount.style.display = 'none';
    }
}
function updatePrice(input) {
    //卡片顯示價格更新
    const productCard = input.closest('.preview-product');
    const priceElement = productCard.querySelector('.product-price');
    const pricePerUnit = parseFloat(priceElement.dataset.price);
    const quantity = input.value;
    const newPrice = pricePerUnit * quantity;
    priceElement.textContent = `$${newPrice}`;


    const productTitle = productCard.querySelector('.card-title').textContent.trim();
    document.querySelectorAll('#summary-list li').forEach(function (item) {
        const itemName = item.querySelector('h6');
        // 需要去掉空白字元, 但為甚麼?
        if (itemName && itemName.textContent.trim() === productTitle) {
            if (quantity != 0) {
                const productTotalElement = item.querySelector('.product-total');
                productTotalElement.textContent = `$${newPrice}`;
            }
            else {
                // 商品數量歸零, 小介面當中的物件也要刪掉
                item.remove();
            }
        }
    });
    updateTotalPrice();
}

function updateTotalPrice() {
    let totalPrice = 0;
    document.querySelectorAll('.preview-product .product-price').forEach(function (priceElement) {
        const price = parseFloat(priceElement.textContent.replace('$', ''));
        totalPrice += price;
    });
    document.getElementById('total-price').textContent = `${totalPrice}`;
}

// 商品數量歸零刪除, 數量減少
document.querySelectorAll('.decrement').forEach(function (button) {
    button.addEventListener('click', function () {
        var input = this.parentNode.querySelector('input[type=number]');
        input.stepDown();
        if (input.value == 0) {
            this.closest('.preview-product').remove();
        }
        MinusCartCount();
        updatePrice(input);
    });
});

// 商品數量增加
document.querySelectorAll('.increment').forEach(function (button) {
    button.addEventListener('click', function () {
        var input = this.parentNode.querySelector('input[type=number]');
        input.stepUp();
        PlusCartCount();
        updatePrice(input);
    });
});

// 直接修改數量輸入框
document.querySelectorAll('.quantity').forEach(function (input) {
    input.addEventListener('change', function () {
        updatePrice(input);
    });
});
