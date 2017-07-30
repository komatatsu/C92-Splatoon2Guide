={printing-book} 入稿戦記

本書の目的は@<chapref>{preface}で書いたとおり、フリーなツールやフォントだけで印刷所に入稿できるのか？の検証なのでやっていく。
入稿用PDFの作成は@<href>{https://hub.docker.com/r/vvakame/review/}で作る。
TeX Live@<fn>{texlive}とNotoフォント@<fn>{noto-font}を利用する。

//footnote[texlive][@<href>{https://www.tug.org/texlive/}]
//footnote[noto-font][@<href>{https://www.google.com/get/noto/}]

==== 07/30 12:32 原稿がとりあえずひととおり終わった

2日前の金曜日の19:04に最初のコミットがあって、日曜日の12:32にとりあえず23P書き終えた。
これからが真の戦いだ…。

オフセットはもう間に合わないのでオンデマンド印刷だ！

==== 07/30 15:19 データ作るぞ

某アレのソレのためにTechBoosterの一部の人間が弊社に集まってきている。

C92で出すRe:VIEW本@<fn>{c92-review}を読むと、PDF/Xに変換とグレースケール化をやったほうがいいらしい。

#@# prh:disable
//footnote[c92-review][@<href>{https://github.com/TechBooster/C89-FirstStepReVIEW-v2}]

近くにtakahashimさんが居たので、「入稿ってPDF/Xでないとだめなんですかね？」と聞いたら「は？」といわれたので別に必須ではないらしい。
日光企画さんのFAQ@<fn>{nikko-faq}によると、RGBで入稿でもCMYK化してくれるそうなので印刷品質にあまりこだわらない技術書としてはそれでいいかという気持ち。

//footnote[nikko-faq][@<href>{http://www.nikko-pc.com/off-faq/off-faq.html}]

グレースケール化は行ってから提出したほうが仕上がりがイメージできそうなので適当にやることにする。
ぐぐった結果、ImageMagickでできるよ！とStackOverflowに書いてあった@<fn>{so-grayscale}ので試してみたらラスタライズしてグレスケしてPDFにしてくれて文字がクッソ荒くなった。
おとなしくGhostscriptでやることにする。

//footnote[so-grayscale][@<href>{https://superuser.com/questions/104656/}]

調べるとGhostscriptには@<i>{Creating a PDF/X-3 document}というドキュメントがあったのでそのオプションの組み合わせを使ってみる。
印刷業界はAdobe様が吐いたPDF以外信用しない文化らしいので、名目上の規格があってたからとそれでよいわけではないらしい。
よって、この配慮に意味があるかは不明だ。

利用するシェルスクリプトは3点。
Re:VIEWのreview-pdfmakerを使ってPDFを作るところまでは割愛する。

//emlist[build-in-docker.sh]{
#@mapfile(../build-in-docker.sh)
#!/bin/bash -eux

docker run -t --rm \
  -v $(pwd):/book vvakame/review \
  /bin/bash -ci "cd /book && ./setup.sh && npm run pdf && ./grayscale.sh"
#@end
//}

//emlist[setup.sh]{
#@mapfile(../setup.sh)
#!/bin/bash -eux

rm -rf node_modules
# --unsafe-perm はrootでの実行時(= docker環境)で必要 非root時の挙動に影響なし
npm install --unsafe-perm
git submodule init && git submodule update
#@end
//}

//emlist[grayscale.sh]{
#@mapfile(../grayscale.sh)
#!/bin/bash -eux

gs \
  -sOutputFile=articles/C92-Splatoon2Guide-gray.pdf \
  -sDEVICE=pdfwrite \
  -dPDFX \
  -dCompatibilityLevel=1.3 \
  -sColorConversionStrategy=Gray \
  -dProcessColorModel=/DeviceGray \
  -dNOPAUSE \
  -dBATCH \
  articles/C92-Splatoon2Guide.pdf
#@end
//}

まずはここで作ったグレースケール化済PDFを入稿データとして使ってみるぞ！

=== 07/30 19:38 A5版に変える

羊がA5版でよくない？と言ったのでA5記念日。

C91のDDD本@<fn>{ddd-book}が印刷版がA5版だったらしいので設定ファイルをにゅるっと移植@<fn>{b5-to-a5}。
過去の資産があるって素晴らしい！

//footnote[ddd-book][@<href>{https://techbooster.booth.pm/items/392260}]
//footnote[b5-to-a5][@<href>{https://github.com/vvakame/C92-Splatoon2Guide/commit/ee3c4ac8776f8162e5ca7e04c2f32474f7834e5c}]

Nintendo Switchで撮影したスクリーンショット、MBPに移す方法がない。
Amazonで@<href>{https://www.amazon.co.jp/gp/product/B071HT25GP/}を注文したんだけどまだ発送されない。
旧MBPにはSDのスロットがあるのでアダプタを家のどこかから発掘して頑張るしかなさそう。
SwitchにDropbox搭載してくれ〜〜〜。

=== 07/30 20:01 日光企画さんに見積もり依頼をかける

表紙データを羊が発注してくれて、イラストレーターさんからのあがりは水曜予定だそうだ。
このクソスケジュールで請けてくれるのすごいと思う。

印刷キューがどうなってるかわからないので電話かメールで印刷所に予約申込の連絡をしろと羊にいわれる。
電話は苦手なのでめるめるします…。
普通に見積もりフォームがあってこれ経由でいいらしい。

部数30部くらいでいい？と羊に相談したら「その葛藤が技術書典参加サークルの葛藤だよ！」といわれた。
確かにそうだなぁ、と思ってとりあえず100部刷ることにした。
みんな100とか200とかバンバン刷ってほしい。
見積もりの依頼を送った！しばらくの間、毎日メールをチェックしなければならない。
#@# estimate.png として見積もりフォーム入力内容を保存
