#pragma once

#include <string.h>

// リングバッファのサイズ
#define RB_SIZE (1024)

// ===================================================================================
// リングバッファクラス by うつぼかずら
// リングバッファについて | C++でVST作り https://www.utsbox.com/?p=1505
// ===================================================================================
class CRingBuffer
{
private:
	int rpos; // 読み込み位置
	int wpos; // 書き込み位置

	float buf[RB_SIZE]; // 内部バッファ

public:
	inline CRingBuffer();

	// 読み込み位置と書き込み位置の間隔を設定する関数
	// ディレイエフェクターの場合はそのまま遅延時間(ディレイタイム)になる
	inline void SetInterval(int interval);

	// 内部バッファの読み込み位置(rpos)のデータを読み込む関数
	// 引数のposは読み込み位置(rpos)からの相対位置
	// (相対位置(pos)はコーラスやピッチシフタなどのエフェクターで利用する)
	inline float Read(int pos = 0);

	// 内部バッファの書き込み位置(wpos)にデータを書き込む関数
	inline void  Write(float in);

	// 内部バッファの読み込み位置(rpos)、書き込み位置(wpos)を一つ進める関数
	inline void Update();
};


// コンストラクタ
CRingBuffer::CRingBuffer()
{
	// 初期化を行う
	rpos = 0;
	wpos = RB_SIZE / 2; // とりあえずバッファサイズの半分ぐらいにしておく

	memset(buf, 0, sizeof(float) * RB_SIZE);
}


// 読み込み位置と書き込み位置の間隔を設定する関数
void CRingBuffer::SetInterval(int interval)
{
	// 読み込み位置と書き込み位置の間隔を設定

	// 値が0以下やバッファサイズ以上にならないよう処理
	interval = interval % RB_SIZE;
	if(interval <= 0) { interval = 1; }
	
	// 書き込み位置を読み込み位置からinterval分だけ離して設定
	wpos = (rpos + interval) % RB_SIZE;
}


// 内部バッファの読み込み位置(rpos)のデータを読み込む関数
float CRingBuffer::Read(int pos)
{
	// 読み込み位置(rpos)と相対位置(pos)から実際に読み込む位置を計算する。
	int tmp = rpos + pos;
	while (tmp < 0)
	{
		tmp += RB_SIZE;
	}
	tmp = tmp %  RB_SIZE; // バッファサイズ以上にならないよう処理

	// 読み込み位置の値を返す
	return buf[tmp];
}


// 内部バッファの書き込み位置(wpos)にデータを書き込む関数
void  CRingBuffer::Write(float in)
{
	// 書き込み位置(wpos)に値を書き込む
	buf[wpos] = in;
}


// 内部バッファの読み込み位置(rpos)、書き込み位置(wpos)を一つ進める関数
void  CRingBuffer::Update()
{
	// 内部バッファの読み込み位置(rpos)、書き込み位置(wpos)を一つ進める
	rpos = (rpos + 1) % RB_SIZE;
	wpos = (wpos + 1) % RB_SIZE;
}
