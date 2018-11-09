<h1> FUNCTION </h1>
<p>
<?php
	function double($alias){
		$alias=$alias * 2;
		return $alias;
	}
	$val=10;
	$dval =double($val);
	echo "value = $val Doubled=$dval \n";
?>
</p>

<p>
	<?php
	function triple(&$realthing){
		$realthing=$realthing * 3;
	}
	$val=10;
	triple($val);
	echo "triple =$val\n";
	?>
</p>


<p>
	<?php
	/*global scope*/
	function dozap(){
		global $val;
		$val=100;
	}
	$val=10;
	dozap();
	echo "DoZap = $val\n";
	?>
</p>


<p>
	<?php
	phpinfo();
	?>
</p>
<p> yes another pararaph.</p>
