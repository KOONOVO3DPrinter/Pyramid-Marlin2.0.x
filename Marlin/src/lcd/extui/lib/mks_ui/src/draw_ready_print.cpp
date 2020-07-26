#include "../../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "../inc/draw_ready_print.h"
#include "../inc/draw_tool.h"
#include "lv_conf.h"
#include "lvgl.h"
//#include "../../lvgl/src/lv_objx/lv_imgbtn.h"
//#include "../../lvgl/src/lv_objx/lv_img.h"
//#include "../../lvgl/src/lv_core/lv_disp.h"
//#include "../../lvgl/src/lv_core/lv_refr.h"
#include "../../../../../module/temperature.h"
#include "../inc/tft_lvgl_configuration.h"
#include "stdio.h"
#include "../inc/mks_hardware_test.h"
#include "../inc/draw_ui.h"


//static lv_obj_t *buttonPrint,*buttonTool,*buttonSet;
static lv_obj_t * scr;
#if ENABLED(MKS_TEST)
uint8_t curent_disp_ui = 0;
#endif

#define ID_SET			1
#define ID_PRINT			2
#define ID_SHUT_DOWN	3
#define ID_PRE_HEAT		4
#define ID_EXTRUCT		5
#define ID_MOV			6
#define ID_HOME			7
#define ID_LEVELING		8
#define ID_TOOL			9

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
	case ID_TOOL:
		if(event == LV_EVENT_CLICKED) {
			
	       }
	       else if(event == LV_EVENT_RELEASED) {
			lv_obj_del(scr);
	        	lv_draw_tool();
	       }
		break;
	case ID_SET:
		if(event == LV_EVENT_CLICKED) {
			
	       }
	       else if(event == LV_EVENT_RELEASED) {
			lv_obj_del(scr);
	        	lv_draw_set();
	       }
		break;
	case ID_PRINT:
		if(event == LV_EVENT_CLICKED) {
			
	       }
	       else if(event == LV_EVENT_RELEASED) {
			lv_obj_del(scr);
	        	lv_draw_print_file();
	       }
		break;
	case ID_SHUT_DOWN:
		if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			#if ENABLED(PSU_CONTROL)
			//queue.enqueue_one_P(PSTR("M81"));
			PSU_OFF();
			#else
			//queue.enqueue_one_P(PSTR("M84"));
			#endif
	    }
	    break;
	    case ID_PRE_HEAT:
	    if(event == LV_EVENT_CLICKED) {
			
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
	        lv_clear_ready_print();
			lv_draw_preHeat();
	    }
		break;
	case ID_EXTRUCT:
		if(event == LV_EVENT_CLICKED) {
			
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
	        lv_clear_ready_print();
		 lv_draw_extrusion();
	    }
		break;
	case ID_MOV:
		if(event == LV_EVENT_CLICKED) {
			
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
	        lv_clear_ready_print();
		 	lv_draw_move_motor();
	    }
		
		break;
	case ID_HOME:
		if(event == LV_EVENT_CLICKED) {
			
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
	        lv_clear_ready_print();
		 lv_draw_home();
	    }
		break;
	case ID_LEVELING:
		if(event == LV_EVENT_CLICKED) {
			
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
	        #if ENABLED(AUTO_BED_LEVELING_BILINEAR)
			queue.enqueue_one_P(PSTR("G28"));
			queue.enqueue_one_P(PSTR("G29"));
			#else
			uiCfg.leveling_first_time = 1;
			lv_clear_ready_print();
		 	lv_draw_manualLevel();
			#endif
	    }
		
		break;

	}
}


#if ENABLED(MKS_TEST)
lv_obj_t *limit_info,*det_info;
lv_style_t limit_style,det_style;
void disp_Limit_ok()
{
	  limit_style.text.color.full = 0xFFFF;
	  lv_obj_set_style(limit_info, &limit_style);
	  lv_label_set_text(limit_info, "Limit:ok");
}
void disp_Limit_error()
{
	  limit_style.text.color.full = 0xF800;
	  lv_obj_set_style(limit_info, &limit_style);
	  lv_label_set_text(limit_info, "Limit:error");
}

void disp_det_ok()
{
	  det_style.text.color.full = 0xFFFF;
	  lv_obj_set_style(det_info, &det_style);
	  lv_label_set_text(det_info, "det:ok");
}
void disp_det_error()
{
	  det_style.text.color.full = 0xF800;
	  lv_obj_set_style(det_info, &det_style);
	  lv_label_set_text(det_info, "det:error");
}

lv_obj_t *e1,*e2,*e3,*bed;
void disp_test()
{
	char buf[30]={0};
	//lv_obj_t * label_tool2 = lv_label_create(scr, NULL);
	//lv_obj_set_pos(label_tool,20,50);
	memset(buf,0,sizeof(buf));
	sprintf(buf,"e1:%d",(int)thermalManager.temp_hotend[0].celsius);
	lv_label_set_text(e1, buf);

	memset(buf,0,sizeof(buf));
	sprintf(buf,"e2:%d",(int)thermalManager.temp_hotend[1].celsius);
	lv_label_set_text(e2, buf);

	memset(buf,0,sizeof(buf));
	sprintf(buf,"e3:%d",(int)thermalManager.temp_hotend[2].celsius);
	lv_label_set_text(e3, buf);

	memset(buf,0,sizeof(buf));
	sprintf(buf,"bed:%d",(int)thermalManager.temp_bed.celsius);
	lv_label_set_text(bed, buf);
}
#endif

void lv_draw_ready_print(uint8_t state)
{
	#if 0
	char buf[30]={0};
	lv_obj_t *buttonTool;
	  
	static lv_style_t style_pr,style_rel;

	curent_disp_ui = 1;
	
	scr = lv_obj_create(NULL, NULL);
	
	static lv_style_t ready_style;
	  
	lv_style_copy(&ready_style, &lv_style_scr);
	//ready_style.body.main_color.full = 0X18C3;
	//ready_style.body.grad_color.full = 0X18C3;
	ready_style.body.main_color.full = 0X0000;
	ready_style.body.grad_color.full = 0X0000;
	ready_style.text.color.full = 0Xffff;
	lv_obj_set_style(scr, &ready_style);
	lv_scr_load(scr);
	lv_obj_clean(scr);
	//lv_obj_set_hidden(scr,true);
	lv_refr_now(lv_refr_get_disp_refreshing());
	  
	LV_IMG_DECLARE(bmp_pic);
	//LV_IMG_DECLARE(bmp_pic2);
	//LV_IMG_DECLARE(bmp_pic3);
	
	//scr = lv_obj_create(NULL, NULL);
	//lv_scr_load(scr);
	  
	/*Create an Image button*/
	buttonTool = lv_imgbtn_create(scr, NULL);
	
	//lv_btn_setting(&style_pr,0x5d8f16,0x5d8f16);
	//lv_btn_setting(&style_rel,0x5d8f16,0x5d8f16);
	  
	lv_obj_set_event_cb_mks(buttonTool, event_handler,3,"bmp_Tool.bin",0);	  
	//lv_imgbtn_set_src_mks(buttonTool, LV_BTN_STATE_REL, &bmp_pic,(uint8_t *)"bmp_tool.bin");
	lv_imgbtn_set_src(buttonTool, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonTool, LV_BTN_STATE_PR, &bmp_pic);   
	lv_imgbtn_set_style(buttonTool, LV_BTN_STATE_PR, &style_pr);
	lv_imgbtn_set_style(buttonTool, LV_BTN_STATE_REL, &style_rel);
	

	 
	lv_obj_set_pos(buttonTool,360,180);
	
	 
	lv_btn_set_layout(buttonTool, LV_LAYOUT_OFF);
	  
	  
	lv_obj_t * label_tool = lv_label_create(buttonTool, NULL);
	  
	lv_obj_set_pos(label_tool,30,100);
	lv_label_set_text(label_tool, "Back");
	  
	e1 = lv_label_create(scr, NULL);
	lv_obj_set_pos(e1,20,20);
	sprintf(buf,"e1:  %d",(int)thermalManager.temp_hotend[0].celsius);
	lv_label_set_text(e1, buf);

	e2 = lv_label_create(scr, NULL);
	lv_obj_set_pos(e2,20,45);
	sprintf(buf,"e1:  %d",(int)thermalManager.temp_hotend[1].celsius);
	lv_label_set_text(e2, buf);

	e3 = lv_label_create(scr, NULL);
	lv_obj_set_pos(e3,20,70);
	sprintf(buf,"e1:  %d",(int)thermalManager.temp_hotend[2].celsius);
	lv_label_set_text(e3, buf);

	bed = lv_label_create(scr, NULL);
	lv_obj_set_pos(bed,20,95);
	sprintf(buf,"bed:  %d",(int)thermalManager.temp_bed.celsius);
	lv_label_set_text(bed, buf);

	limit_info = lv_label_create(scr, NULL);

	lv_style_copy(&limit_style, &lv_style_scr);
	limit_style.body.main_color.full = 0X0000;
	limit_style.body.grad_color.full = 0X0000;
	limit_style.text.color.full = 0Xffff;
	lv_obj_set_style(limit_info, &limit_style);
	
	lv_obj_set_pos(limit_info,20,120);
	lv_label_set_text(limit_info, " ");

	det_info = lv_label_create(scr, NULL);

	lv_style_copy(&det_style, &lv_style_scr);
	det_style.body.main_color.full = 0X0000;
	det_style.body.grad_color.full = 0X0000;
	det_style.text.color.full = 0Xffff;
	lv_obj_set_style(det_info, &det_style);
	
	lv_obj_set_pos(det_info,20,145);
	lv_label_set_text(det_info, " ");

	#endif

	lv_obj_t *buttonPreHeat,*buttonExtrusion,*buttonMove,*buttonHome,*buttonLevel;
	lv_obj_t *buttonPrint,*buttonSet,*buttonShutDown,*buttonTool;

	buttonPreHeat = 0;
	buttonExtrusion = 0;
	buttonMove= 0;
	buttonHome = 0;
	buttonLevel = 0;
	buttonPrint = 0;
	buttonSet = 0;
	buttonShutDown = 0;
	buttonTool = 0;
	
	if(state == 0)
	{
		disp_state_stack._disp_index = 0;
		memset(disp_state_stack._disp_state, 0, sizeof(disp_state_stack._disp_state));
		disp_state_stack._disp_state[disp_state_stack._disp_index] = PRINT_READY_UI;
		
		disp_state = PRINT_READY_UI;

		scr = lv_obj_create(NULL, NULL);

		lv_obj_set_style(scr, &tft_style_scr);
	  	lv_scr_load(scr);
	  	lv_obj_clean(scr);
	  	//lv_obj_set_hidden(scr,true);
	  	lv_refr_now(lv_refr_get_disp_refreshing());
		
		LV_IMG_DECLARE(bmp_pic);

		//lv_obj_t * title = lv_label_create(scr, NULL);
		//lv_obj_set_style(title, &tft_style_lable_rel);
		//lv_obj_set_pos(title,TITLE_XPOS,TITLE_YPOS);
		//lv_label_set_text(title, creat_title_text());
		
	    /*Create an Image button*/
	    buttonPrint = lv_imgbtn_create(scr, NULL);
		buttonTool = lv_imgbtn_create(scr, NULL);
		buttonSet = lv_imgbtn_create(scr, NULL);
		buttonShutDown = lv_imgbtn_create(scr, NULL);

		lv_obj_set_event_cb_mks(buttonPrint, event_handler,ID_PRINT,"bmp_Print.bin",0);
	    //lv_imgbtn_set_src_mks(buttonPrint, LV_BTN_STATE_REL, &bmp_pic,(uint8_t *)"bmp_printing.bin");
		lv_imgbtn_set_src(buttonPrint, LV_BTN_STATE_REL, &bmp_pic);
		lv_imgbtn_set_src(buttonPrint, LV_BTN_STATE_PR, &bmp_pic);
		lv_imgbtn_set_style(buttonPrint, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonPrint, LV_BTN_STATE_REL, &tft_style_lable_rel);
		lv_obj_clear_protect(buttonPrint, LV_PROTECT_FOLLOW);
		#if 1
		lv_obj_set_event_cb_mks(buttonSet, event_handler,ID_SET,"bmp_Set.bin",0);
	    //lv_imgbtn_set_src_mks(buttonSet, LV_BTN_STATE_REL, &bmp_pic,(uint8_t *)"bmp_set.bin");
		lv_imgbtn_set_src(buttonSet, LV_BTN_STATE_REL, &bmp_pic);
		lv_imgbtn_set_src(buttonSet, LV_BTN_STATE_PR, &bmp_pic);
		lv_imgbtn_set_style(buttonSet, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonSet, LV_BTN_STATE_REL, &tft_style_lable_rel);
		
		lv_obj_set_event_cb_mks(buttonTool, event_handler,ID_TOOL,"bmp_Tool.bin",0);	
	    //lv_imgbtn_set_src_mks(buttonTool, LV_BTN_STATE_REL, &bmp_pic,(uint8_t *)"bmp_tool.bin");
	    lv_imgbtn_set_src(buttonTool, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonTool, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonTool, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonTool, LV_BTN_STATE_REL, &tft_style_lable_rel);

		lv_obj_set_event_cb_mks(buttonShutDown, event_handler,ID_SHUT_DOWN,"bmp_Mamual.bin",0);	
	    //lv_imgbtn_set_src_mks(buttonShutDown, LV_BTN_STATE_REL, &bmp_pic,(uint8_t *)"bmp_tool.bin");
	    lv_imgbtn_set_src(buttonShutDown, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonShutDown, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonShutDown, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonShutDown, LV_BTN_STATE_REL, &tft_style_lable_rel);

		#endif
		lv_obj_set_pos(buttonTool,BTN_X_PIXEL+INTERVAL_V*2,90);
		lv_obj_set_pos(buttonSet,BTN_X_PIXEL*2+INTERVAL_V*3,90);
		lv_obj_set_pos(buttonPrint,INTERVAL_V,90);
		lv_obj_set_pos(buttonShutDown,BTN_X_PIXEL*3+INTERVAL_V*4,  90);


		//lv_obj_set_pos(buttonTool,20,90);
		//lv_obj_set_pos(buttonSet,180,90);
		//lv_obj_set_pos(buttonPrint,340,90);

	    /*Create a label on the Image button*/
		lv_btn_set_layout(buttonPrint, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonSet, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonTool, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonShutDown, LV_LAYOUT_OFF);
		
	    lv_obj_t * label_print = lv_label_create(buttonPrint, NULL);
		lv_obj_t * label_set = lv_label_create(buttonSet, NULL);
		lv_obj_t * label_tool = lv_label_create(buttonTool, NULL);
		lv_obj_t * label_shut_down = lv_label_create(buttonShutDown, NULL);
		if(gCfgItems.multiple_language !=0)
		{
			
			lv_label_set_text(label_print, main_menu.print);
			lv_obj_align(label_print, buttonPrint, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
			
			lv_label_set_text(label_set, main_menu.set);
			lv_obj_align(label_set, buttonSet, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

			//lv_label_set_style(label_tool,LV_BTN_STATE_PR,&tft_style_lable_pre);
			//lv_label_set_style(label_tool,LV_BTN_STATE_REL,&tft_style_lable_rel);
			lv_label_set_text(label_tool, main_menu.tool);
			lv_obj_align(label_tool, buttonTool, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

			
			lv_label_set_text(label_shut_down, set_menu.shutdown);
			lv_obj_align(label_shut_down, buttonShutDown, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		}
	}
	else
	{
		disp_state_stack._disp_index = 0;
		memset(disp_state_stack._disp_state, 0, sizeof(disp_state_stack._disp_state));
		disp_state_stack._disp_state[disp_state_stack._disp_index] = PRINT_READY_UI;
		
		disp_state = PRINT_READY_UI;

		scr = lv_obj_create(NULL, NULL);

		//static lv_style_t tool_style;
		
		lv_obj_set_style(scr, &tft_style_scr);
	  lv_scr_load(scr);
	  lv_obj_clean(scr);

	  lv_obj_t * title = lv_label_create(scr, NULL);
		lv_obj_set_style(title, &tft_style_lable_rel);
		lv_obj_set_pos(title,TITLE_XPOS,TITLE_YPOS);
		lv_label_set_text(title, creat_title_text());
	  
	  lv_refr_now(lv_refr_get_disp_refreshing());
		
		LV_IMG_DECLARE(bmp_pic);
		
	    /*Create an Image button*/
	       buttonPreHeat = lv_imgbtn_create(scr, NULL);
		buttonMove = lv_imgbtn_create(scr, NULL);
		buttonHome = lv_imgbtn_create(scr, NULL);
		buttonPrint = lv_imgbtn_create(scr, NULL);
		buttonExtrusion = lv_imgbtn_create(scr, NULL);
		buttonLevel = lv_imgbtn_create(scr, NULL);
		buttonSet = lv_imgbtn_create(scr, NULL);
		buttonShutDown = lv_imgbtn_create(scr, NULL);

		
		lv_obj_set_event_cb_mks(buttonPreHeat, event_handler,ID_PRE_HEAT,"bmp_PreHeat.bin",0);
		lv_imgbtn_set_src(buttonPreHeat, LV_BTN_STATE_REL, &bmp_pic);
		lv_imgbtn_set_src(buttonPreHeat, LV_BTN_STATE_PR, &bmp_pic);
		lv_imgbtn_set_style(buttonPreHeat, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonPreHeat, LV_BTN_STATE_REL, &tft_style_lable_rel);
		lv_obj_clear_protect(buttonPreHeat, LV_PROTECT_FOLLOW);
		#if 1
		

		lv_obj_set_event_cb_mks(buttonMove, event_handler,ID_MOV,"bmp_Mov.bin",0);	
	    lv_imgbtn_set_src(buttonMove, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonMove, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonMove, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonMove, LV_BTN_STATE_REL, &tft_style_lable_rel);

		lv_obj_set_event_cb_mks(buttonHome, event_handler,ID_HOME,"bmp_Zero.bin",0);	
	    lv_imgbtn_set_src(buttonHome, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonHome, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonHome, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonHome, LV_BTN_STATE_REL, &tft_style_lable_rel);

		lv_obj_set_event_cb_mks(buttonPrint, event_handler,ID_PRINT,"bmp_Print.bin",0);	
	    lv_imgbtn_set_src(buttonPrint, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonPrint, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonPrint, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonPrint, LV_BTN_STATE_REL, &tft_style_lable_rel);

		lv_obj_set_event_cb_mks(buttonExtrusion, event_handler,ID_EXTRUCT,"bmp_Extruct.bin",0);
		lv_imgbtn_set_src(buttonExtrusion, LV_BTN_STATE_REL, &bmp_pic);
		lv_imgbtn_set_src(buttonExtrusion, LV_BTN_STATE_PR, &bmp_pic);
		lv_imgbtn_set_style(buttonExtrusion, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonExtrusion, LV_BTN_STATE_REL, &tft_style_lable_rel);

		lv_obj_set_event_cb_mks(buttonLevel, event_handler,ID_LEVELING,"bmp_Leveling.bin",0);	
	    lv_imgbtn_set_src(buttonLevel, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonLevel, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonLevel, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonLevel, LV_BTN_STATE_REL, &tft_style_lable_rel);

		lv_obj_set_event_cb_mks(buttonSet, event_handler,ID_SET,"bmp_Set.bin",0);	
	    lv_imgbtn_set_src(buttonSet, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonSet, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonSet, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonSet, LV_BTN_STATE_REL, &tft_style_lable_rel);

		lv_obj_set_event_cb_mks(buttonShutDown, event_handler,ID_SHUT_DOWN,"bmp_Mamual.bin",0);	
	    lv_imgbtn_set_src(buttonShutDown, LV_BTN_STATE_REL, &bmp_pic);
	    lv_imgbtn_set_src(buttonShutDown, LV_BTN_STATE_PR, &bmp_pic);	
		lv_imgbtn_set_style(buttonShutDown, LV_BTN_STATE_PR, &tft_style_lable_pre);
		lv_imgbtn_set_style(buttonShutDown, LV_BTN_STATE_REL, &tft_style_lable_rel);

		#endif
		
		/*lv_obj_set_pos(buttonPreHeat,INTERVAL_V,titleHeight);
		lv_obj_set_pos(buttonMove,BTN_X_PIXEL+INTERVAL_V*2,titleHeight);
		lv_obj_set_pos(buttonHome,BTN_X_PIXEL*2+INTERVAL_V*3,titleHeight);
		lv_obj_set_pos(buttonPrint,BTN_X_PIXEL*3+INTERVAL_V*4,titleHeight);
		lv_obj_set_pos(buttonExtrusion,INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		lv_obj_set_pos(buttonLevel,BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		lv_obj_set_pos(buttonSet,BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		lv_obj_set_pos(buttonShutDown,BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		*/
		lv_obj_set_pos(buttonPreHeat,INTERVAL_V,titleHeight);
		lv_obj_set_pos(buttonMove,BTN_X_PIXEL+INTERVAL_V*2,titleHeight);
		lv_obj_set_pos(buttonHome,BTN_X_PIXEL*2+INTERVAL_V*3,titleHeight);
		lv_obj_set_pos(buttonPrint,BTN_X_PIXEL*3+INTERVAL_V*4,titleHeight);
		lv_obj_set_pos(buttonExtrusion,INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		lv_obj_set_pos(buttonLevel,BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		lv_obj_set_pos(buttonSet,BTN_X_PIXEL*2+INTERVAL_V*3,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		lv_obj_set_pos(buttonShutDown,BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
		
	    /*Create a label on the Image button*/
		lv_btn_set_layout(buttonPreHeat, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonExtrusion, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonMove, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonHome, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonLevel, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonSet, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonPrint, LV_LAYOUT_OFF);
		lv_btn_set_layout(buttonShutDown, LV_LAYOUT_OFF);
		
	    	lv_obj_t * labelPreHeat = lv_label_create(buttonPreHeat, NULL);
		lv_obj_t * label_Move = lv_label_create(buttonMove, NULL);
		lv_obj_t * label_Home = lv_label_create(buttonHome, NULL);
		lv_obj_t * label_Print = lv_label_create(buttonPrint, NULL);
		
		lv_obj_t * labelExtrusion = lv_label_create(buttonExtrusion, NULL);
		lv_obj_t * label_Level = lv_label_create(buttonLevel, NULL);
		lv_obj_t * label_Set = lv_label_create(buttonSet, NULL);
		lv_obj_t * label_ShutDown = lv_label_create(buttonShutDown, NULL);
		
		
		if(gCfgItems.multiple_language !=0)
		{
		    lv_label_set_text(labelPreHeat, tool_menu.preheat);
			lv_obj_align(labelPreHeat, buttonPreHeat, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

			lv_label_set_text(label_Move, tool_menu.move);
			lv_obj_align(label_Move, buttonMove, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

		    lv_label_set_text(label_Home, tool_menu.home);
			lv_obj_align(label_Home, buttonHome, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

			lv_label_set_text(label_Print, main_menu.print);
			lv_obj_align(label_Print, buttonPrint, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

			lv_label_set_text(labelExtrusion, tool_menu.extrude);
			lv_obj_align(labelExtrusion, buttonExtrusion, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

			/*if(gCfgItems.leveling_mode != 2)
			{
				if(gCfgItems.leveling_mode == 1)
					lv_label_set_text(label_Level, tool_menu.autoleveling);
				else
					lv_label_set_text(label_Level, tool_menu.leveling);
				
				lv_obj_align(label_Level, buttonLevel, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
			}*/
			#if ENABLED(AUTO_BED_LEVELING_BILINEAR)
			lv_label_set_text(label_Level, tool_menu.autoleveling);
			#else
			lv_label_set_text(label_Level, tool_menu.leveling);
			#endif
			lv_obj_align(label_Level, buttonLevel, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
			
			lv_label_set_text(label_Set, main_menu.set);
			lv_obj_align(label_Set, buttonSet, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

			lv_label_set_text(label_ShutDown, set_menu.shutdown);
			lv_obj_align(label_ShutDown, buttonShutDown, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		}
	}
}


void lv_clear_ready_print()
{
	lv_obj_del(scr);
}

#endif
