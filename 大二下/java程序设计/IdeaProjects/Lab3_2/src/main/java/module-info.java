module com.example.lab3_2 {
    requires javafx.controls;
    requires javafx.fxml;
    requires java.desktop;


    opens com.example.lab3_2 to javafx.fxml;
    exports com.example.lab3_2;
}