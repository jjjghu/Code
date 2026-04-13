softmax 改 log_softmax 會比較好。
將同一個 batch 收集的路通通標準化
取樣時超出範圍的需要 clamp 之後存入 actions 當中，否則用在環境上與實際計算的東西不一樣


問題	位置	影響
存入未 clamp 的 action → log_prob 計算對象錯誤	trainer.py:86-88	訓練梯度方向錯誤
sigmoid + 無 hover bias 初始化	model.py:59	早期大量墜毀，梯度信號極差
sigma 最大可達 2.72	model.py:62	加劇 Bug 1 的影響範圍
隱藏層 clamp 截斷梯度	model.py:58/85	部分神經元無法更新