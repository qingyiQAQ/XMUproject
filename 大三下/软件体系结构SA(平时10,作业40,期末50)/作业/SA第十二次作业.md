# SA第十二次作业

1、修改本例，增加一个新的concrete的Builder。

定义一个新的MarkdownBuilder继承自抽象类Builder，用于生成Markdown文件

重写各个方法，如下：

```java
public class MarkdownBuilder extends Builder {
    private StringBuilder markdown = new StringBuilder();

    public void makeTitle(String title) {
        markdown.append("# ").append(title).append("\n\n");
    }

    public void makeString(String str) {
        markdown.append("## ").append(str).append("\n\n");
    }

    public void makeItems(String[] items) {
        for (String item : items) {
            markdown.append("- ").append(item).append("\n");
        }
        markdown.append("\n");
    }

    public Object getResult() {
        return markdown.toString();
    }
}
```

改写Main函数

```java
public class Main {
    public static void main(String[] args) {
        if (args.length != 1) {
            //System.out.println(args.length);
            usage();
            System.exit(0);
        }
        if (args[0].equals("plain")) {
            Director director = new Director(new TextBuilder());
            String result = (String) director.construct();
            System.out.println(result);
        } else if (args[0].equals("html")) {
            Director director = new Director(new HTMLBuilder());
            String filename = (String) director.construct();
            System.out.println("已产生" + filename + "。");
        } else if (args[0].equals("markdown")) {
            Director director = new Director(new MarkdownBuilder());
            String result = (String) director.construct();
            System.out.println(result);
        } else {
            usage();
            System.exit(0);
        }
    }

    public static void usage() {
        System.out.println("Usage: java Main plain  产生一般格式的文件");
        System.out.println("Usage: java Main html   产生HTML格式的文件");
        System.out.println("Usage: java Main html   产生Markdown格式的文件");
    }
}
```

运行结果：

![image-20240506204802858](C:\Users\CC507\AppData\Roaming\Typora\typora-user-images\image-20240506204802858.png)