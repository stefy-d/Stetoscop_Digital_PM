<h1 align="center"><strong>STETOSCOP DIGITAL</strong></h1>

<table width="100%">
<tr>
<td align="left"><span style="font-size:18px"><strong>Manea Ștefania-Delia</strong></span></td>
<td align="right"><span style="font-size:18px"><strong>Grupa 335CC</strong></span></td>
</tr>
</table>

<br>


 
## *Introducere*

Proiectul propune realizarea unui stetoscop digital, capabil să capteze sunetele corpului uman prin intermediul unui microfon de înaltă sensibilitate. Utilizatorul va putea începe sau opri înregistrarea prin intermediul unui buton, iar starea va fi indicată de un led aprins verde dacă este pornită sau roșu altfel. Cât timp înregistrarea este pornită, pe ecranul OLED va fi afișată reprezentarea grafică a semnalului captat de microfon.

Semnalul audio va fi amplificat și filtrat utilizând configurații specifice de filtre, în scopul îmbunătățirii clarității și calității sunetelor percepute. Redarea sunetului se va realiza printr-un difuzor conectat la un amplificator audio, iar volumul va putea fi ajustat cu ajutorul unui potențiometru rotativ.

## *Descriere generală*

Arduino Nano reprezintă centrul de control al proiectului, ocupându-se de colectarea datelor, procesarea semnalelor și gestionarea interfeței cu utilizatorul. La acesta sunt conectate următoarele module:

+ **Microfon MAX4466** – Captează sunetele produse de corpul uman. Semnalul analogic generat este trimis către un pin ADC al microcontrollerului, unde este amplificat și pregătit pentru procesare.
+ **Amplificator audio PAM8403** – Primește semnalul audio procesat și îl amplifică pentru a fi redat cu claritate. Este conectat la un difuzor de 3 W, ce redă sunetul în timp real.
+ **Difuzor miniatural** – Conectat la ieșirea amplificatorului, asigură redarea clară a sunetelor auscultate.
+ **Ecran OLED** – Afișează tipul de ascultare selectat (ex: cardiac, pulmonar) și alte informații relevante.
+ **Potențiometru rotativ** – Permite ajustarea manuală a volumului. Semnalul său analogic este citit de Arduino printr-un pin ADC.
+ **Butoane** – Folosite pentru pornirea/oprirea înregistrării. Semnalele digitale de la butoane sunt interpretate de Arduino pentru a schimba comportamentul sistemului și afișajul.
+ **LED RGB** - Indică în ce stare se află înregistrarea.


<br>

![Schema Proiect](DIAGRAMA.drawio.png)

<br>

## *Hardware Design*

**Funcționalitatea generală HW**
Sistemul hardware este format dintr-un **microfon MAX4466** care captează sunetul din mediu și trimite semnalul analogic rezultat către **Arduino Nano pe pinul A0** pentru analiză și afișare. Microfonul este alimentat la 5V și GND. Afișajul OLED afișează în timp real forma de undă a semnalului audio, fiind conectat la pinii **A4 (SDA) și A5 (SCL)** ai Arduino-ului prin **protocol I²C**. Arduino Nano funcționează ca unitate centrală de control, citind semnalul de la microfon, gestionând afișajul, LED-urile, difuzorul și stările logice ale sistemului. **Două butoane** conectate la **pinii D2 și D3** sunt utilizate pentru a iniția și opri înregistrarea, fiecare fiind conectat la GND prin **rezistențe de pull-down**. Feedback-ul vizual este oferit de un **LED RGB** cu anod comun, al cărui segment verde (pe **D5**) indică starea de repaus, iar segmentul roșu (pe **D4**) pâlpâie în timpul înregistrării. Controlul volumului este realizat printr-un potențiometru montat între ieșirea de semnal și **amplificatorul audio PAM8403**, care reglează tensiunea de intrare și permite ajustarea sunetului perceput în difuzor. Amplificatorul este alimentat la 5V și transmite semnalul audio amplificat către difuzor pentru redare clară.

**Listă de piese:**
+ [Arduino Nano](https://www.optimusdigital.ro/en/compatible-with-arduino-nano/1686-development-board-arduino-nano-compatible-atmega328p-ch340.html?gad_source=1&gad_campaignid=19615979487&gbraid=0AAAAADv-p3BfEEZZl7O_k8PCbMoE1d4yA&gclid=CjwKCAjw_pDBBhBMEiwAmY02Npo2m4ip9HTy-tlA6H_U-An1zd4d-CkBcl3BxZET9_fcyFJ03iXX7xoCEqgQAvD_BwE) 
+ [Modul microfon MAX4466 cu amplificare si castig reglabil](https://sigmanortec.ro/modul-microfon-max4466-cu-amplificare-castig-reglabil-23-5vdc?SubmitCurrency=1&id_currency=2&gad_source=1&gad_campaignid=22174019478&gbraid=0AAAAAC3W72Mtzy7jY3q2IvRJJL2399kKi&gclid=CjwKCAjw_pDBBhBMEiwAmY02NjoiHoMMp2m7MvMgD5IMIKWO3YSxMbl3gWkBP3i0PlqeKFrk4SYHbhoCJd4QAvD_BwE)
+ [Modul Mini Amplificator in Clasa D Stereo PAM8403 de 3 W](https://sigmanortec.ro/modul-amplificator-miniatura-pam8403-22-5v?SubmitCurrency=1&id_currency=2&gad_source=1&gad_campaignid=22174019478&gbraid=0AAAAAC3W72Mtzy7jY3q2IvRJJL2399kKi&gclid=CjwKCAjw_pDBBhBMEiwAmY02Nv4Kh82h7hM4exmOleI9l1nKFCEOkJXp0H4xaOj1xKOyClULKjlmchoCRUEQAvD_BwE)
+ [Difuzor Mini, 3 Wati](https://www.emag.ro/difuzor-mini-3-wati-8-ohmi-pentru-arduino-diy-gd-0135/pd/DSSX18YBM/)
+ [Ecran OLED 0.96”](https://sigmanortec.ro/display-oled-096-i2c-iic-alb?SubmitCurrency=1&id_currency=2&gad_source=1&gad_campaignid=22174019478&gbraid=0AAAAAC3W72Mtzy7jY3q2IvRJJL2399kKi&gclid=CjwKCAjw_pDBBhBMEiwAmY02Nkg1IQK_EUcACBMSpldrDa0FIDTmlGddDwTUg6q6EU_xLhcgTZfY4RoCxKYQAvD_BwE)
+ [Potențiometru rotativ](https://www.optimusdigital.ro/en/potentiometers/1887-100k-mono-potentiometer.html?gad_source=1&gad_campaignid=19615979487&gbraid=0AAAAADv-p3BfEEZZl7O_k8PCbMoE1d4yA&gclid=CjwKCAjw_pDBBhBMEiwAmY02Np0TkkPLCOFwRPMUOY6n5pKcIBN2whddkB2a2r2Mub2G8ekJFebs3BoCaBEQAvD_BwE)
+ [Butoane](https://sigmanortec.ro/buton-mini-6x6x5-4-pini?SubmitCurrency=1&id_currency=2&gad_source=1&gad_campaignid=22174019478&gbraid=0AAAAAC3W72Mtzy7jY3q2IvRJJL2399kKi&gclid=CjwKCAjw_pDBBhBMEiwAmY02NpxfK8MtKIF-iWQKl6GAaAhgb36NExmekoQhD_qB1ldQNoiYYklYBhoCu1EQAvD_BwE)
+ [LED RGB](https://sigmanortec.ro/LED-RGB-5mm-4-pini-Catod-comun-p136284849?SubmitCurrency=1&id_currency=2&gad_source=1&gad_campaignid=22174019478&gbraid=0AAAAAC3W72Mtzy7jY3q2IvRJJL2399kKi&gclid=CjwKCAjw_pDBBhBMEiwAmY02NpXqShHs5yZXH-7NuQuPmsTUzHCgz7o_y7E58lyUDhFF_HLYKFX6AhoCqikQAvD_BwE)
+ [Rezistențe de 5k1 Ohm](https://www.optimusdigital.ro/en/resistors/853-025w-51k-resistor.html)

**Conectare componente**

| Componentă      | Pin                         | Motivație                                               |
|-----------------|-----------------------------|----------------------------------------------------------|
| Microfon        | A0                          | Folosit pentru afișaj                                    |
| Microfon        | A1                          | Folosit pentru transmitere la difuzor                    |
| Display OLED    | A4 (SDA), A5 (SCL)          | Comunicare I2C Arduino-Display                           |
| Potențiometru   | A0                          | Reglează semnalul primit de la microfon și îl trimite la amplificator |
| Amplificator    | Semnal potențiometru        | Trimite semnal audio amplificat către difuzor            |
| Difuzor         | A1                          | Controlează alimentarea pozitivă a amplificatorului      |
| LED RGB         | D4 (Red), D5 (Green)        | Feedback de stare vizual                                 |
| Buton 1         | D2                          | Start înregistrare                                       |
| Buton 2         | D3                          | Oprire și revenire la starea inițială                    |

![Schema](schematic.png)
<br>

![Schema Electrica](schema_electrica.png)





