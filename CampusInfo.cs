using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using TMPro;

public class CampusInfo : MonoBehaviour
{
    public string distanceFromSaddleback;
    public string souvenirType;
    public float souvenirPrice;
    private bool isUsernameAuthenticated = false;
    private bool isPasswordAuthenticated = false;
    public Transform campusListBackground;

    public GameObject mainMenu;
    public GameObject adminLogIn;
    public GameObject adminSettings;
    public GameObject displayCampusesPage;
    public GameObject purchasesPage;
    public GameObject planYourTripPage;
    public GameObject campusListPrf;
    public GameObject logInBox;
    public GameObject errorBox;
    public GameObject backButton;
    public TextMeshPro campusNameText;
    public TMP_InputField username;
    public TMP_InputField password;


    public List<string> campusName = new List<string>();
    public List<GameObject> campusPlaceholder = new List<GameObject>();

    void Start()
    {
        campusName.Add("University of Wisconsin (UW)\n");
        campusName.Add("University of the Pacific (UP)\n");
        campusName.Add("Univeristy of Texas (UT)\n");
        campusName.Add("University of Orego (UO)\n");
        campusName.Add("University of California, Los Angeles (UCLA)\n");
        campusName.Add("University of California, Irvine (UCI)\n");
        campusName.Add("University of Michigan (UM) \n");
        campusName.Add("Saddleback College (SC)\n");
        campusName.Add("Ohio State University (OSU)\n");
        campusName.Add("Northwestern University (NU)\n");
        campusName.Add("Massachusetts Institute of Technology (MIT)\n");
        campusName.Add("California State University, Fullerton (CSUF)\n");
        campusName.Add("Arizona State University (ASU)\n");

        for (int i = 0; i < 12; i++)
        {
            campusListPrf.transform.position = new Vector3(182, 130 + i * 34, 0);
            GameObject newCampus = Instantiate(campusListPrf, campusListPrf.transform.position, campusListBackground.rotation);
            campusPlaceholder.Add(newCampus);
            newCampus.transform.SetParent(campusListBackground.transform);
            TMP_Text campusText = newCampus.GetComponentInChildren<TMP_Text>() as TMP_Text;
            campusText.text = campusName.ElementAt(i) + "- 0000 Miles";

        }
    }

    public void OnDisplayCampusesClicked()
    {
        mainMenu.SetActive(false);
        displayCampusesPage.SetActive(true);
        
    }

    public void OnPurchasesPageClicked()
    {
        mainMenu.SetActive(false);
        purchasesPage.SetActive(true);
    }

    public void OnPlanYourTripClicked()
    {
        mainMenu.SetActive(false);
        planYourTripPage.SetActive(true);
    }

    public void OnBackButtonClicked()
    {
        if(displayCampusesPage.activeSelf == true)
        {
            displayCampusesPage.SetActive(false);
        }

        if (planYourTripPage.activeSelf == true)
        {
            planYourTripPage.SetActive(false);
        }

        if (purchasesPage.activeSelf == true)
        {
            purchasesPage.SetActive(false);
        }

        mainMenu.SetActive(true);
    }

    public void OnAdminClicked()
    {
        mainMenu.SetActive(false);
        displayCampusesPage.SetActive(false);
        errorBox.SetActive(false);
        adminLogIn.SetActive(true);

    }

    public void OnAuthentication()
    {
        if (username.text == "admin" && password.text == "admin")
        {
            adminLogIn.SetActive(false);
            adminSettings.SetActive(true);
        }

        else
        {
            logInBox.SetActive(false);
            backButton.SetActive(false);
            errorBox.SetActive(true);
        }

        username.text = null;
        password.text = null;
    }

    public void OnErrorBackClicked()
    {
        errorBox.SetActive(false);
        logInBox.SetActive(true);
        backButton.SetActive(true);
    }

}
