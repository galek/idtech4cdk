﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

using ToolsManaged.Private;
using ToolsManaged.Private.idLib;
using ToolsManaged.Frontend.WindowAPI;

using ToolsManaged.Private.Editor;
namespace ToolsManaged.Frontend
{
    public partial class EntityProperties : Form
    {
        

        private idLibNativeAPI.idDictNative _dict;
        private idLibNativeAPI.idDictNative _templateDict;
        public EntityProperties()
        {
            InitializeComponent();
        }

        private void UpdateEntityPropertiesControl()
        {
            _dict.childDict = NativeAPI.Entity_GetTemplate(_dict.GetString("classname"));


            entitiesPropertyCntrl.SelectedObject = _dict;
            entitiesPropertyCntrl.Refresh();
        }

        private void UpdateProperties()
        {
            // Update the properties dialog.
            UpdateEntityPropertiesControl();

            // Update the title.
            this.Text = "Properties for " + _dict.GetString( "name" );
        }

        private void UpdateOrigin(Vector3 origin)
        {

            OriginXTxt.Text = String.Format("{0:0.0}", origin.x);
            OriginYTxt.Text = String.Format("{0:0.0}", origin.y);
            OriginZTxt.Text = String.Format("{0:0.0}", origin.z);
        }

        public void ShowWindow(idLibNativeAPI.idDictNative dict)
        {
            _dict = dict;

            UpdateProperties();

            ShowDialog();
        }

        private void EntityProperties_Load(object sender, EventArgs e)
        {

        }

        private void assignModelBtn_Click(object sender, EventArgs e)
        {
            string rootModelPath = "generated/models";
            OpenFileDialog dialog = new OpenFileDialog();

            dialog.InitialDirectory = NativeAPI.FileSystem.RelativePathToOSPath(rootModelPath);
            dialog.Filter = "Static Model (*.md5staticmesh)|*.md5staticmesh";
            dialog.FilterIndex = 1;

            if (dialog.ShowDialog() == DialogResult.OK)
            {
                string relpath = dialog.FileName.Substring(dialog.InitialDirectory.Length - (rootModelPath.Length + 1));

        
                _dict.Set("model", relpath);
                _dict.Set("vthandletype", "" + EditorUVGenerateType.Editor_GenerateUVs_Orient);
                entitiesPropertyCntrl.Refresh();

                NativeAPI.UpdateBrush();
                FormManager.handle.ForceRepaint();
            }

        }

        private void entitiesPropertyCntrl_Click(object sender, EventArgs e)
        {

        }

      
    }
}
