<!--
{
	"author": "lxf",
	"title": "UNICODE编码方案",
	"date": "2019-12-30 00:09:04",
	"category": "其他"
}
-->

UNICODE编码方案
------------------------------------------------------------
2019-12-30 00:09:04 &emsp;   

UNICODE最多占用4个字节32位  
取值范围：0x00000000-0x0010FFFF  
编码范围：1114112  

UNICODE字符集编码方案: UTF-8 | UTF-16  

<table>
	<caption>UTF-16编码方案</caption>
	<tr>
	    <th>区</th>
	    <th>取值范围</th>
		<th>字节</th>
	</tr>
	<tr>
	    <td>多语言字符区</td>
	    <td>0x00000000-0x0000FFFF</td>
		<td>两字节</td>
	</tr>
	<tr>
	    <td>辅助平面区</td>
	    <td>0x00100000-0x0010FFFF</td>
		<td>四字节</td>
	</tr>
</table>

<table>
	<caption>UTF-8编码方案</caption>
	<tr>
	    <th>Unicode编码(16进制)</th>
	    <th>UTF-8 字节流(二进制)</th>
		<th>字节</th>
	</tr>
	<tr>
	    <td>000000 - 00007F</td>
	    <td>0xxxxxxx</td>
		<td>一字节</td>
	</tr>
	<tr>
	    <td>000080 - 0007FF</td>
	    <td>110xxxxx 10xxxxxx</td>
		<td>两字节</td>
	</tr>
	<tr>
	    <td>000800 - 00FFFF</td>
	    <td>1110xxxx 10xxxxxx 10xxxxxx</td>
		<td>三字节</td>
	</tr>
	<tr>
	    <td>010000 - 10FFFF</td>
	    <td>11110xxx 10xxxxxx 10xxxxxx 10xxxxxx</td>
		<td>四字节</td>
	</tr>
</table>

<table>
	<caption>BOM(Byte Order Mark)</caption>
	<tr>
	    <th>编码方案</th>
		<th>指纹</th>
	</tr>
	<tr>
	    <td>UTF-8</td>
	    <td>EF BB BF</td>
	</tr>
	<tr>
	    <td>UTF-16LE</td>
	    <td>FF FE</td>
	</tr>
	<tr>
	    <td>UTF-16BE</td>
	    <td>FE FF</td>
	</tr>
</table>



------------------------------------------------------------
[返回上级目录](./../../../../categories/其他/README.md)&emsp;|&emsp;[返回首页](./../../../../README.md)