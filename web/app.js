
         function autocomplete(searchEle, arr) {
            var currentFocus;
            
            searchEle.addEventListener("input", function(e) {
               var divCreate,
               b,
               fieldVal = this.value;
               closeAllLists();
               if (!fieldVal) {
                  return false;
               }
               currentFocus = -1;
               divCreate = document.createElement("DIV");
               divCreate.setAttribute("id", this.id + "autocomplete-list");
               divCreate.setAttribute("class", "autocomplete-items");
               this.parentNode.appendChild(divCreate);
               for (var i = 0; i <arr.length; i++) {
                  if ( arr[i].substr(0, fieldVal.length).toUpperCase() == fieldVal.toUpperCase() ) {
                     b = document.createElement("DIV");
                     b.innerHTML = "<strong>" + arr[i].substr(0, fieldVal.length) + "</strong>";
                     b.innerHTML += arr[i].substr(fieldVal.length);
                     b.innerHTML += "<input type='hidden' value='" + arr[i] + "'>";
                     b.addEventListener("click", function(e) {
                        searchEle.value = this.getElementsByTagName("input")[0].value;
                        closeAllLists();
                     });
                     divCreate.appendChild(b);
                  }
               }
            });
            searchEle.addEventListener("keydown", function(e) {
               var autocompleteList = document.getElementById(
                  this.id + "autocomplete-list"
               );
               if (autocompleteList)
                  autocompleteList = autocompleteList.getElementsByTagName("div");
               if (e.keyCode == 40) {
                  currentFocus++;
                  addActive(autocompleteList);
               }
               else if (e.keyCode == 38) {
                  //up
                  currentFocus--;
                  addActive(autocompleteList);
               }
               else if (e.keyCode == 13) {
                  e.preventDefault();
                  if (currentFocus > -1) {
                     if (autocompleteList) autocompleteList[currentFocus].click();
                  }
               }
            });
            function addActive(autocompleteList) {
               if (!autocompleteList) return false;
                  removeActive(autocompleteList);
               if (currentFocus >= autocompleteList.length) currentFocus = 0;
               if (currentFocus < 0) currentFocus = autocompleteList.length - 1;
               autocompleteList[currentFocus].classList.add("autocomplete-active");
            }
            function removeActive(autocompleteList) {
               for (var i = 0; i < autocompleteList.length; i++) {
                  autocompleteList[i].classList.remove("autocomplete-active");
               }
            }
            function closeAllLists(elmnt) {
               var autocompleteList = document.getElementsByClassName(
                  "autocomplete-items"
               );
               for (var i = 0; i < autocompleteList.length; i++) {
                  if (elmnt != autocompleteList[i] && elmnt != searchEle) {
                     autocompleteList[i].parentNode.removeChild(autocompleteList[i]);
                  }
               }
            }
            document.addEventListener("click", function(e) {
               closeAllLists(e.target);
            });
         }
         
         
         
         
         var animals = [
         "Aba",
         "Abak",
         "Abakaliki",
         "Abeokuta",
         "Abocho",
         "Abraka",
         "Abuja",
         "Adani",
         "Ado-Ekiti",
         "Ado-Odo",
         "Adoru",
         "Afikpo",
         "Agaie",
         "Agbabu",
         "Agbor",
         "Agenebode",
         "Ago-Are",
         "Agulu",
         "Ahoada",
         "Ajaokuta",
         "Ajasse Ipo",
         "Akankpa",
         "Ake-Eze",
         "Akko",
         "Aku",
         "Akure",
         "Akwanga",
         "Alapa",
         "Aliade",
         "Amagunze",
         "Amaigbo",
         "Amassoma",
         "Amper",
         "Anchau",
         "Anka",
         "Ankpa",
         "Apomu",
         "Aramoko-Ekiti",
         "Argungu",
         "Arochukwu",
         "Asaba",
         "Atani",
         "Auchi",
         "Auna",
         "Awgu",
         "Awka",
         "Azare",
         "Babana",
         "Babura",
         "Badagry",
         "Badeggi",
         "Bagudo",
         "Baissa",
         "Bakori",
         "Bama",
         "Bara",
         "Baro",
         "Batsari",
         "Bauchi",
         "Bebeji",
         "Beli",
         "Bena",
         "Bende",
         "Benin City",
         "Benisheikh",
         "Bida",
         "Billiri",
         "Bin Yauri",
         "Binji",
         "Birnin Kebbi",
         "Birnin Kudu",
         "Birniwa",
         "Biu",
         "Bode Saadu",
         "Boi",
         "Boju",
         "Bokani",
         "Bokkos",
         "Bomadi",
         "Bonny",
         "Bori",
         "Bornu Yassu",
         "Buga",
         "Bugana",
         "Buguma",
         "Bukuru",
         "Bununu",
         "Burumburum",
         "Burutu",
         "Calabar",
         "Chakwama",
         "Dabai",
         "Dadiya",
         "Dakingari",
         "Damasak",
         "Damaturu",
         "Dambatta",
         "Damboa",
         "Dan Gora",
         "Dan Sadau",
         "Dange",
         "Danja",
         "Dankalwa",
         "Dankama",
         "Dapchi",
         "Darazo",
         "Dass",
         "Daura",
         "Daura",
         "Deba",
         "Degema Hulk",
         "Dekina",
         "Dengi",
         "Dikwa",
         "Dindima",
         "Disina",
         "Doma",
         "Dukku",
         "Duku",
         "Dutse",
         "Dutsen Wai",
         "Dutsin-Ma",
         "Ebute Ikorodu",
         "Effium",
         "Efon-Alaaye",
         "Egbe",
         "Eha Amufu",
         "Ejigbo",
         "Ejirin",
         "Eket",
         "Ekpoma",
         "Elele",
         "Emure-Ekiti",
         "Enugu",
         "Enugu-Ezike",
         "Enugu-Ukwu",
         "Epe",
         "Esuk Oron",
         "Ete",
         "Etinan",
         "Ezza-Ohu",
         "Fiditi",
         "Funtua",
         "Gabarin",
         "Gagarawa",
         "Gakem",
         "Gamawa",
         "Gamboru",
         "Gandi",
         "Ganye",
         "Garko",
         "Gashua",
         "Gassol",
         "Gaya",
         "Gbongan",
         "Geidam",
         "Gembu",
         "Gombe",
         "Gombi",
         "Goniri",
         "Gora",
         "Gorgoram",
         "Goronyo",
         "Gujba",
         "Gulma",
         "Gumel",
         "Gummi",
         "Gusau",
         "Gwadabawa",
         "Gwandu",
         "Gwaram",
         "Gwaram",
         "Gwarzo",
         "Gwasoro",
         "Gwio Kura",
         "Gwoza",
         "Hadejia",
         "Hinna",
         "Holma",
         "Hunkuyi",
         "Ibadan",
         "Ibeto",
         "Ibi",
         "Icheu",
         "Idah",
         "Idanre",
         "Idiroko",
         "Ifaki",
         "Ifo",
         "Ifon",
         "Igabi",
         "Igarra",
         "Igbara-Odo",
         "Igbeti",
         "Igbo-Ora",
         "Igbo-Ukwu",
         "Igboho",
         "Igbor",
         "Igede-Ekiti",
         "Ihiala",
         "Iho",
         "Ijebu-Ife",
         "Ijebu-Igbo",
         "Ijebu-Jesa",
         "Ijebu-Ode",
         "Ijero-Ekiti",
         "Ikang",
         "Ikeja",
         "Ikem",
         "Ikere-Ekiti",
         "Ikire",
         "Ikirun",
         "Ikom",
         "Ikot Ekpene",
         "Ila Orangun",
         "Ilare",
         "Ilaro",
         "Ilesa",
         "Illela",
         "Illushi",
         "Ilobu",
         "Ilorin",
         "Imeko",
         "Inisa",
         "Iperu",
         "Ipoti",
         "Isanlu-Itedoijowa",
         "Isara",
         "Ise-Ekiti",
         "Isieke",
         "Itu",
         "Iwo",
         "Jalingo",
         "Jebba",
         "Jega",
         "Jibia",
         "Jikamshi",
         "Jimeta",
         "Jos",
         "Kabba",
         "Kachia",
         "Kaduna",
         "Kafanchan",
         "Kafarati",
         "Kafin Hausa",
         "Kagoro",
         "Kaiama",
         "Kajuru",
         "Kaltungo",
         "Kamba",
         "Kangiwa",
         "Kankara",
         "Kano",
         "Kari",
         "Katagum",
         "Katsina",
         "Katsina-Ala",
         "Kaura Namoda",
         "Kazaure",
         "Keffi",
         "Kende",
         "Kibiya",
         "Kisi",
         "Kiyawa",
         "Konduga",
         "Konkwesso",
         "Kontagora",
         "Koton-Karfe",
         "Kujama",
         "Kuje",
         "Kukawa",
         "Kumagunnam",
         "Kumo",
         "Kura",
         "Kusheriki",
         "Kuta",
         "Kwale",
         "Kwali",
         "Kwatarkwashi",
         "Kwolla",
         "Lafia",
         "Lafiagi",
         "Lagos",
         "Lajere",
         "Lalupon",
         "Lame",
         "Langtang",
         "Lapai",
         "Lau",
         "Lekki",
         "Lere",
         "Lere",
         "Lokoja",
         "Machina",
         "Madagali",
         "Madala",
         "Madara",
         "Magumeri",
         "Mahuta",
         "Maiduguri",
         "Maiyama",
         "Makurdi",
         "Mallammaduri",
         "Malumfashi",
         "Mando",
         "Marte",
         "Maru",
         "Mashi",
         "Mayo-Belwa",
         "Mberubu",
         "Minna",
         "Miringa",
         "Misau",
         "Modakeke",
         "Mokwa",
         "Monguno",
         "Moriki",
         "Mubi",
         "Musawa",
         "Mutum Biyu",
         "Nafada",
         "Nasarawa",
         "New Shagunnu",
         "Ngala",
         "Ngurore",
         "Nguru",
         "Nkpor",
         "Nkwerre",
         "Nnewi",
         "Nsukka",
         "Numan",
         "Obiaruku",
         "Obolo-Eke (1)",
         "Obonoma",
         "Obubra",
         "Obudu",
         "Ochobo",
         "Ode",
         "Offa",
         "Ogaminana",
         "Ogoja",
         "Ogurugu",
         "Oguta",
         "Ogwashi-Uku",
         "Ohafia-Ifigh",
         "Oke Ila",
         "Oke Mesi",
         "Okeho",
         "Okene",
         "Okigwe",
         "Okrika",
         "Okuta",
         "Olupona",
         "Omoku",
         "Omu-Aran",
         "Omuo-Ekiti",
         "Ondo",
         "Onitsha",
         "Opi",
         "Ore",
         "Orerokpe",
         "Orita Eruwa",
         "Orlu",
         "Orodo",
         "Osogbo",
         "Otan Ayegbaju",
         "Otukpa",
         "Owerri",
         "Owo",
         "Owode",
         "Oyan",
         "Oyo",
         "Ozubulu",
         "Pankshin",
         "Panyam",
         "Patani",
         "Patigi",
         "Pindiga",
         "Port Harcourt",
         "Potiskum",
         "Rabah",
         "Rano",
         "Rijau",
         "Ringim",
         "Riti",
         "Ruma",
         "Runka",
         "Sade",
         "Saki",
         "Samamiya",
         "Saminaka",
         "Sapele",
         "Sauri",
         "Shaffa",
         "Shagamu",
         "Shanga",
         "Shani",
         "Shinkafi",
         "Siluko",
         "Soba",
         "Sofo-Birnin-Gwari",
         "Sokoto",
         "Suleja",
         "Suya",
         "Takai",
         "Takum",
         "Talata Mafara",
         "Tambuwal",
         "Tegina",
         "Tokombere",
         "Toungo",
         "Tsafe",
         "Twon-Brass",
         "Uba",
         "Ubiaja",
         "Udi",
         "Uga",
         "Ugbokpo",
         "Ugep",
         "Ughelli",
         "Ukata",
         "Umuahia",
         "Umunede",
         "Uromi",
         "Uruobo-Okija",
         "Uyo",
         "Vom",
         "Wagini",
         "Wamba",
         "Warri",
         "Wasagu",
         "Wawa",
         "Wudil",
         "Wukari",
         "Wurno",
         "Wuyo",
         "Yajiwa",
         "Yamrat",
         "Yanda Bayo",
         "Yandev",
         "Yashikira",
         "Yelwa",
         "Yenagoa",
         "Yola",
         "Yuli",
         "Zadawa",
         "Zaki Biam",
         "Zalanga",
         "Zango",
         "Zaria",
         "Zungeru",
         "Zuru"
         ];
         
         autocomplete(document.getElementById("searchField1"), animals);
         autocomplete(document.getElementById("searchField2"), animals);
         
         function canvas_arrow(context, fromx, fromy, tox, toy) {
            var headlen = 10; // length of head in pixels
            var dx = tox - fromx;
            var dy = toy - fromy;
            var angle = Math.atan2(dy, dx);
            context.moveTo(fromx, fromy);
            context.lineTo(tox, toy);
            context.lineTo(tox - headlen * Math.cos(angle - Math.PI / 6), toy - headlen * Math.sin(angle - Math.PI / 6));
            context.moveTo(tox, toy);
            context.lineTo(tox - headlen * Math.cos(angle + Math.PI / 6), toy - headlen * Math.sin(angle + Math.PI / 6));
         }
         
         
         const check = (e) => {
            
            const form = new FormData(e.target);
            const cityA = form.get("city1");
            const cityB = form.get("city2");
         
         var retVector = Module['Dijkstra'](cityA, cityB);
         
         var vectorSize = retVector.size();
         
          
         var c=document.getElementById("myfillDrawing");
         var ctx=c.getContext("2d");
         ctx.strokeStyle= "#000000";
         ctx.lineWidth = 0.5;
         ctx.strokeRect(30, 0, 1500, 500);
         ctx.clearRect(30, 0, 1500, 500);
         ctx.fillStyle = "black";
         ctx.font = "18px Arial";
         ctx.fillText( "The distance from "+ cityA + " to " + cityB + " is " +retVector.get(0) +" Km" , 135, 55);
         ctx.fillText( " Paths to follow :" , 150, 100);
         
         
         for (var i = 1; i < retVector.size(); i++) {
           
            ctx.fillText(retVector.get(i), 100 + i*150, 155);
            canvas_arrow(ctx, 100 + i*150 + 100, 150, 100 + i*150 + 130, 150);
            ctx.stroke();
            
         }
         
         return false
         };
         
         
          