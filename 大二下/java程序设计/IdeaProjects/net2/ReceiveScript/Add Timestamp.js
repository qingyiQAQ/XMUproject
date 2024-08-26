/********************************
 * 
 * Notes:  添加时间戳
 * 
 * 在接收数据前添加时间戳
 * 
 * 
 *******************************/

(
    function main() {
        var d=new Date();
        
        // 格式1  2021/3/9上午10:48:59-> 年/月/日 时:分:秒
        // receive.write(d.toLocaleString( )+"-> ","red");
        
        // 格式2 10:48:59.671  h:m:s.ms 时:分:秒.毫秒
        var h=d.getHours().toString().padStart(2,'0');
        var m=d.getMinutes().toString().padStart(2,'0');
        var s=d.getSeconds().toString().padStart(2,'0');
        var ms=d.getMilliseconds().toString().padStart(3,'0');
        var str=h+":"+m+":"+s+"."+ms;
        receive.write(str +"-> ","red"); // 发送时间 颜色红色

        var strRead=receive.get();
        if(receive.isAutoBreakFrame()==false) //未启用自动断帧时添加回车换行符.
            receive.write(strRead+"\r\n"); 
        else
            receive.write(strRead);
        return ;
    }
)()

