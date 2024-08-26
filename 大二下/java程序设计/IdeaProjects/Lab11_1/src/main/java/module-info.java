module com.example.lab11_1 {
    requires javafx.controls;
    requires javafx.fxml;


    opens com.example.lab11_1 to javafx.fxml;
    exports com.example.lab11_1;
}