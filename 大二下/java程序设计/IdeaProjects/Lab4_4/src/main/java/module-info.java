module com.example.lab4_4 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens com.example.lab4_4 to javafx.fxml;
    exports com.example.lab4_4;
}