package com.example.lab10_2;

// Fig. 26.6: PainterController.java
// Controller for the Painter app
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Toggle;
import javafx.scene.control.ToggleGroup;
import javafx.scene.input.MouseDragEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.AnchorPane;
import javafx.scene.paint.Color;
import javafx.scene.paint.Paint;
import javafx.scene.shape.*;
import javafx.scene.canvas.Canvas;
import javafx.scene.shape.Shape;

import java.util.regex.Pattern;

public class PainterController
{
    // enum representing pen sizes
    private enum PenSize
    {
        SMALL(2),
        MEDIUM(4),
        LARGE(6);

        private final int radius;

        PenSize(int radius)
        {
            this.radius = radius;
        }

        public int getRadius()
        {
            return radius;
        }
    };

    // instance variables that refer to GUI components
    @FXML private RadioButton blackRadioButton;
    @FXML private RadioButton redRadioButton;
    @FXML private RadioButton greenRadioButton;
    @FXML private RadioButton blueRadioButton;
    @FXML private RadioButton smallRadioButton;
    @FXML private RadioButton mediumRadioButton;
    @FXML private RadioButton largeRadioButton;
    @FXML private AnchorPane drawingAreaAnchorPane;
    @FXML private ToggleGroup colorToggleGroup;
    @FXML private ToggleGroup sizeToggleGroup;
    @FXML private RadioButton lineButton;
    @FXML private RadioButton rectangleButton;
    @FXML private RadioButton circleButton;
    @FXML private RadioButton pointButton;
    @FXML private ToggleGroup typeGroup;


    // instance variables for managing Painter state
    private PenSize radius = PenSize.MEDIUM; // radius of circle
    private Paint brushColor = Color.BLACK; // drawing color
    private double x1,x2,y1,y2;

    // set user data for the RadioButtons
    public void initialize()
    {
        // user data on a control can be any Object
        blackRadioButton.setUserData(Color.BLACK);
        redRadioButton.setUserData(Color.RED);
        greenRadioButton.setUserData(Color.GREEN);
        blueRadioButton.setUserData(Color.BLUE);
        smallRadioButton.setUserData(PenSize.SMALL);
        mediumRadioButton.setUserData(PenSize.MEDIUM);
        largeRadioButton.setUserData(PenSize.LARGE);
        typeGroup.selectToggle(pointButton);
    }

    // handles drawingArea's onMouseDragged MouseEvent
    @FXML
    private void drawingAreaMouseDragged(MouseEvent e)
    {
        Toggle selectedType = typeGroup.getSelectedToggle();
        if(selectedType==pointButton){
            Circle newCircle = new Circle(e.getX(), e.getY(), radius.getRadius(), brushColor);
            drawingAreaAnchorPane.getChildren().add(newCircle);
        }

    }
    @FXML
    public void drawingAreaMousePressed(MouseEvent e){
        x1=e.getX();
        y1=e.getY();
    }
    @FXML
    public void drawingAreaMouseReleased(MouseEvent e){
        Toggle selectedType = typeGroup.getSelectedToggle();
        x2=e.getX();
        y2=e.getY();
        if(selectedType==circleButton){
            Circle newCircle = new Circle((x1+x2)/2,(y1+y2)/2,Math.sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1))/2, brushColor);
            drawingAreaAnchorPane.getChildren().add(newCircle);
        }
        if(selectedType==rectangleButton){
            Rectangle newRectangle = new Rectangle(0,0,brushColor);
            newRectangle.setX(x1);
            newRectangle.setY(y1);
            newRectangle.setHeight(y2-y1);
            newRectangle.setWidth(x2-x1);
            drawingAreaAnchorPane.getChildren().add(newRectangle);
        }
        if(selectedType==lineButton){
            Line newLine = new Line(x1,y1,x2,y2);
            newLine.setStroke(brushColor);
            newLine.setStrokeWidth(radius.getRadius());
            drawingAreaAnchorPane.getChildren().add(newLine);
        }
    }

    // handles color RadioButton's ActionEvents
    @FXML
    private void colorRadioButtonSelected(ActionEvent e)
    {
        // user data for each color RadioButton is the corresponding Color
        brushColor =
                (Color) colorToggleGroup.getSelectedToggle().getUserData();
    }

    // handles size RadioButton's ActionEvents
    @FXML
    private void sizeRadioButtonSelected(ActionEvent e)
    {
        // user data for each size RadioButton is the corresponding PenSize
        radius =
                (PenSize) sizeToggleGroup.getSelectedToggle().getUserData();
    }

    // handles Undo Button's ActionEvents
    @FXML
    private void undoButtonPressed(ActionEvent event)
    {
        int count = drawingAreaAnchorPane.getChildren().size();

        // if there are any shapes remove the last one added
        if (count > 0)
            drawingAreaAnchorPane.getChildren().remove(count - 1);
    }

    // handles Clear Button's ActionEvents
    @FXML
    private void clearButtonPressed(ActionEvent event)
    {
        drawingAreaAnchorPane.getChildren().clear(); // clear the canvas
    }
}

/**************************************************************************
 * (C) Copyright 1992-2018 by Deitel & Associates, Inc. and               *
 * Pearson Education, Inc. All Rights Reserved.                           *
 *                                                                        *
 * DISCLAIMER: The authors and publisher of this book have used their     *
 * best efforts in preparing the book. These efforts include the          *
 * development, research, and testing of the theories and programs        *
 * to determine their effectiveness. The authors and publisher make       *
 * no warranty of any kind, expressed or implied, with regard to these    *
 * programs or to the documentation contained in these books. The authors *
 * and publisher shall not be liable in any event for incidental or       *
 * consequential damages in connection with, or arising out of, the       *
 * furnishing, performance, or use of these programs.                     *
 *************************************************************************/