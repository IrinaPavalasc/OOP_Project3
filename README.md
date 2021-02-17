# OOP_Project3
Third assignment in my OOP class, year 1.

Pizzeria X testează un nou soft, dezvoltat în maniera OOP, pentru gestionarea activității sale. Codul
propriu-zis contine o clasa abstracta care contine doar metoda virtuala pura de calcul al prețului unui produs,
iar din aceasta clasa deriva clasa Pizza. În realizarea oricărui produs intra un anumit număr de ingrediente
pentru care se cunosc denumirile, cantitatile și prețul unitar. Prețul unui produs finit este data de prețul
ingredientelor plus manopera (o suma constanta fixată de producător). Daca pizza este comandata OnLine, la
preț se mai adaugă și 5% din pret la fiecare 10 km parcursi de angajatul care livrează la domiciliu.
Structura de date: unordered_map sau unordered_set &lt;id_pizza, list sau vector &lt;ingredient&gt;&gt;
Cerința suplimentară:
- Să se adauge toate campurile relevante pentru modelarea acestei probleme.
- Să se construiască clasa template Meniu care sa gestioneze tipurie de pizza comercializate. Clasa trebuie sa
contina indexul unui produs (incrementat automat la vanzarea unui produs prin supraincarcarea operatorului
+=) și o structură de date, alocata dinamic.
- Să se construiască o specializare pentru tipul Comanda_Online care sa trateze tipurile de pizza vegetariana
într-un document contabil separat din care sa rezulte valoarea totala incasata din vanzarea acestora.
