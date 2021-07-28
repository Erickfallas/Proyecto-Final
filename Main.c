#include <stdio.h>
#include <gtk/gtk.h>
#include <math.h>

GtkWidget *buttons[3][3];
int jugador_actual;

typedef struct {
  int x;
  int y;
}coordinate;


void limpiar_tablero() {
  int x;
  for ( x = 0; x < 3; x++) {
    int y;
    for ( y = 0; y < 3; y++) {
      gtk_button_set_label(GTK_BUTTON(buttons[x][y]),"");
    }
  }
}

void marcar_tablero (GtkButton *button, gpointer userdata) {
  coordinate *c = userdata;
  int t = strlen(gtk_button_get_label(button));
  if (strlen(gtk_button_get_label(button)) == 0) {
    switch (jugador_actual) {
      case 1:
        gtk_button_set_label(GTK_BUTTON(buttons[c->x][c->y]),"X");
        jugador_actual=2;
        
        break;
      case 2:
        gtk_button_set_label(GTK_BUTTON(buttons[c->x][c->y]),"O");
        jugador_actual=1;
        break;
      default:
        break;
    }
  }
  return;
}

int main (int argc, char *argv[]){
  gtk_init(&argc, &argv);

  GtkWidget *window;
  GtkWidget *vbox;
  GtkWidget *hbox_top, *hbox_bottom;
  GtkWidget *label_jugador_1, *label_jugador_2, *label_vs;
  GtkWidget *grid_1;
  GtkWidget *child;
  GtkWidget *button_new_game;

  jugador_actual=1;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);{
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    gtk_window_set_default_size (GTK_WINDOW(window),300,400);
    gtk_window_set_resizable(GTK_WINDOW(window),FALSE);
    gtk_window_set_position (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_window_set_title (GTK_WINDOW(window), "TIC TAC TOE");
      vbox = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
        gtk_container_add (GTK_CONTAINER(window),GTK_WIDGET(vbox));
        gtk_box_set_spacing(GTK_BOX(vbox),10);
        gtk_widget_set_margin_start(GTK_WIDGET(vbox),5);
        gtk_widget_set_margin_end(GTK_WIDGET(vbox),5);
        gtk_widget_set_margin_bottom(GTK_WIDGET(vbox),5);
        gtk_widget_set_margin_top(GTK_WIDGET(vbox),5);
        hbox_top = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);{
          gtk_box_set_homogeneous (GTK_BOX(hbox_top), TRUE);
          gtk_container_add (GTK_CONTAINER(vbox), GTK_WIDGET(hbox_top));
          label_jugador_1 = gtk_label_new (NULL);
            gtk_container_add(GTK_CONTAINER(hbox_top), label_jugador_1);
            gtk_label_set_markup(GTK_LABEL(label_jugador_1),"<b> Jugador 1:      X</b>");
          label_vs = gtk_label_new (NULL);
            gtk_container_add(GTK_CONTAINER(hbox_top), label_vs);
            gtk_label_set_markup(GTK_LABEL(label_vs),"<b>VS</b>");
          label_jugador_2 = gtk_label_new (NULL);
            gtk_container_add(GTK_CONTAINER(hbox_top), label_jugador_2);
            gtk_label_set_markup(GTK_LABEL(label_jugador_2),"<b>O      :Jugador 2 </b>");
        }
        grid_1=gtk_grid_new ();{
          gtk_container_add (GTK_CONTAINER(vbox), grid_1);
          gtk_grid_set_row_spacing(GTK_GRID(grid_1),5);
          gtk_grid_set_column_spacing(GTK_GRID(grid_1),5);
          gtk_grid_set_row_homogeneous(GTK_GRID(grid_1),TRUE);
          gtk_grid_set_column_homogeneous(GTK_GRID(grid_1),TRUE);
          gtk_widget_set_vexpand(GTK_WIDGET(grid_1),TRUE);
          for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
              coordinate *c = malloc(sizeof *c);
              c->x = i;
              c->y = j;
              buttons[i][j]=gtk_button_new_with_label("");
              gtk_grid_attach(GTK_GRID(grid_1),buttons[i][j],i,j,1,1);
              g_signal_connect(GTK_BUTTON(buttons[i][j]),"clicked",G_CALLBACK(marcar_tablero),c);
            }
          }        
        }
        hbox_bottom = gtk_box_new (GTK_ORIENTATION_HORIZONTAL,0);{
          gtk_container_add(GTK_CONTAINER(vbox),GTK_WIDGET(hbox_bottom));
          gtk_box_set_homogeneous (GTK_BOX(hbox_bottom), TRUE);
          button_new_game=gtk_button_new_with_label("New Game");
          gtk_container_add(GTK_CONTAINER(hbox_bottom),GTK_WIDGET(button_new_game));
          g_signal_connect(GTK_WIDGET(button_new_game),"clicked",G_CALLBACK(limpiar_tablero),NULL);
        }
  gtk_widget_show_all (window);
  gtk_main();
  }
}