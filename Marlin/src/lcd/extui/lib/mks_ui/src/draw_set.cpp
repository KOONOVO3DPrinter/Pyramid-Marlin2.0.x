#include "../../../../../MarlinCore.h"
#if ENABLED(TFT_LITTLE_VGL_UI)
#include "../inc/draw_ready_print.h"
#include "../inc/draw_set.h"
#include "lv_conf.h"
//#include "../../lvgl/src/lv_objx/lv_imgbtn.h"
//#include "../../lvgl/src/lv_objx/lv_img.h"
//#include "../../lvgl/src/lv_core/lv_disp.h"
//#include "../../lvgl/src/lv_core/lv_refr.h"
#include "../inc/draw_ui.h"
#include "../../../../../gcode/queue.h"

static lv_obj_t * scr;

#define ID_S_WIFI			1
#define ID_S_FAN				2
#define ID_S_ABOUT			3
#define ID_S_CONTINUE		4
#define ID_S_MOTOR_OFF		5
#define ID_S_LANGUAGE		6
#define ID_S_RETURN			7
#define ID_S_X_MODE			8
#define ID_S_EEPROM_SET	9

static void event_handler(lv_obj_t * obj, lv_event_t event)
{
	switch(obj->mks_obj_id)
	{
	case ID_S_WIFI:
	    if(event == LV_EVENT_CLICKED) {
			
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
	        
	    }
		break;
	case ID_S_FAN:
		if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			lv_obj_del(scr);
	        	lv_draw_fan();
	    }
		break;
	case ID_S_ABOUT:
		if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			lv_obj_del(scr);
	        	lv_draw_about();
	    }
		break;
	case ID_S_CONTINUE:
		
		break;
	/*case ID_S_MOTOR_OFF:
		if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			#if ENABLED(PSU_CONTROL)
			queue.enqueue_one_P(PSTR("M81"));
			PSU_OFF();
			//digitalWrite(PS_ON_PIN, LOW);
			#else
			queue.enqueue_one_P(PSTR("M84"));
			#endif
	    }
		break;*/
	case ID_S_LANGUAGE:
		if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			lv_obj_del(scr);
	        	lv_draw_language();
	    }
		break;
	case ID_S_RETURN:
	    if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			lv_obj_del(scr);
	        	lv_draw_ready_print(1);
	    }
		break;
	#if ENABLED(DUAL_X_CARRIAGE)
		case ID_S_X_MODE:
	    if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
			lv_obj_del(scr);
	        	lv_draw_x_mode();
	    }
		break;
		#endif
	case ID_S_EEPROM_SET:
	    if(event == LV_EVENT_CLICKED) {
			
	    }
	    else if(event == LV_EVENT_RELEASED) {
	        	lv_obj_del(scr);
	        	lv_draw_eeprom_settings();
	    }
		break;

	}
}


void lv_draw_set(void)
{
	lv_obj_t *buttonFan,*buttonAbout;
	lv_obj_t *buMotorOff,*buttonLanguage,*buttonBack;
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_t *buttonXmode;
	#endif
	lv_obj_t *buttonEepromSet;

	if(disp_state_stack._disp_state[disp_state_stack._disp_index] != SET_UI)
	{
		disp_state_stack._disp_index++;
		disp_state_stack._disp_state[disp_state_stack._disp_index] = SET_UI;
	}
	disp_state = SET_UI;

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
       //buttonWifi = lv_imgbtn_create(scr, NULL);
	buttonFan = lv_imgbtn_create(scr, NULL);
	buttonAbout = lv_imgbtn_create(scr, NULL);
	//buttonContinue = lv_imgbtn_create(scr, NULL);
	//buMotorOff = lv_imgbtn_create(scr, NULL);
	buttonLanguage = lv_imgbtn_create(scr, NULL);
	buttonBack = lv_imgbtn_create(scr, NULL);
	#if ENABLED(DUAL_X_CARRIAGE)
	buttonXmode = lv_imgbtn_create(scr, NULL);
	#endif
	buttonEepromSet = lv_imgbtn_create(scr, NULL);
	
	//lv_obj_set_event_cb_mks(buttonWifi, event_handler,ID_S_WIFI,"bmp_Wifi.bin",0);
	//lv_imgbtn_set_src(buttonWifi, LV_BTN_STATE_REL, &bmp_pic);
	//lv_imgbtn_set_src(buttonWifi, LV_BTN_STATE_PR, &bmp_pic);
	//lv_imgbtn_set_style(buttonWifi, LV_BTN_STATE_PR, &tft_style_lable_pre);
	//lv_imgbtn_set_style(buttonWifi, LV_BTN_STATE_REL, &tft_style_lable_rel);
	//lv_obj_clear_protect(buttonWifi, LV_PROTECT_FOLLOW);
	#if 1
	lv_obj_set_event_cb_mks(buttonFan, event_handler,ID_S_FAN,"bmp_Fan.bin",0);
	lv_imgbtn_set_src(buttonFan, LV_BTN_STATE_REL, &bmp_pic);
	lv_imgbtn_set_src(buttonFan, LV_BTN_STATE_PR, &bmp_pic);
	lv_imgbtn_set_style(buttonFan, LV_BTN_STATE_PR, &tft_style_lable_pre);
	lv_imgbtn_set_style(buttonFan, LV_BTN_STATE_REL, &tft_style_lable_rel);

	lv_obj_set_event_cb_mks(buttonAbout, event_handler,ID_S_ABOUT,"bmp_About.bin",0);	
    lv_imgbtn_set_src(buttonAbout, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonAbout, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonAbout, LV_BTN_STATE_PR, &tft_style_lable_pre);
	lv_imgbtn_set_style(buttonAbout, LV_BTN_STATE_REL, &tft_style_lable_rel);

	//lv_obj_set_event_cb_mks(buttonContinue, event_handler,ID_S_CONTINUE,"bmp_Breakpoint.bin",0);	
    //lv_imgbtn_set_src(buttonContinue, LV_BTN_STATE_REL, &bmp_pic);
    //lv_imgbtn_set_src(buttonContinue, LV_BTN_STATE_PR, &bmp_pic);	
	//lv_imgbtn_set_style(buttonContinue, LV_BTN_STATE_PR, &tft_style_lable_pre);
	//lv_imgbtn_set_style(buttonContinue, LV_BTN_STATE_REL, &tft_style_lable_rel);
	//#if ENABLED(PSU_CONTROL)
	//lv_obj_set_event_cb_mks(buMotorOff, event_handler,ID_S_MOTOR_OFF,"bmp_Mamual.bin",0);
	//#else
	//lv_obj_set_event_cb_mks(buMotorOff, event_handler,ID_S_MOTOR_OFF,"bmp_Motor_off.bin",0);
	//#endif
    //lv_imgbtn_set_src(buMotorOff, LV_BTN_STATE_REL, &bmp_pic);
   // lv_imgbtn_set_src(buMotorOff, LV_BTN_STATE_PR, &bmp_pic);	
	//lv_imgbtn_set_style(buMotorOff, LV_BTN_STATE_PR, &tft_style_lable_pre);
	//lv_imgbtn_set_style(buMotorOff, LV_BTN_STATE_REL, &tft_style_lable_rel);

	lv_obj_set_event_cb_mks(buttonLanguage, event_handler,ID_S_LANGUAGE,"bmp_Language.bin",0);	
    lv_imgbtn_set_src(buttonLanguage, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonLanguage, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonLanguage, LV_BTN_STATE_PR, &tft_style_lable_pre);
	lv_imgbtn_set_style(buttonLanguage, LV_BTN_STATE_REL, &tft_style_lable_rel);

	lv_obj_set_event_cb_mks(buttonBack, event_handler,ID_S_RETURN,"bmp_Return.bin",0);	
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonBack, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_PR, &tft_style_lable_pre);
	lv_imgbtn_set_style(buttonBack, LV_BTN_STATE_REL, &tft_style_lable_rel);

	#endif

	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_set_event_cb_mks(buttonXmode, event_handler,ID_S_X_MODE,"bmp_X_mode.bin",0);	
    	lv_imgbtn_set_src(buttonXmode, LV_BTN_STATE_REL, &bmp_pic);
    	lv_imgbtn_set_src(buttonXmode, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonXmode, LV_BTN_STATE_PR, &tft_style_lable_pre);
	lv_imgbtn_set_style(buttonXmode, LV_BTN_STATE_REL, &tft_style_lable_rel);
	#endif

	lv_obj_set_event_cb_mks(buttonEepromSet, event_handler,ID_S_EEPROM_SET,"bmp_Eeprom_settings.bin",0);	
    lv_imgbtn_set_src(buttonEepromSet, LV_BTN_STATE_REL, &bmp_pic);
    lv_imgbtn_set_src(buttonEepromSet, LV_BTN_STATE_PR, &bmp_pic);	
	lv_imgbtn_set_style(buttonEepromSet, LV_BTN_STATE_PR, &tft_style_lable_pre);
	lv_imgbtn_set_style(buttonEepromSet, LV_BTN_STATE_REL, &tft_style_lable_rel);
	
	/*lv_obj_set_pos(buttonWifi,INTERVAL_V,titleHeight);
	lv_obj_set_pos(buttonFan,BTN_X_PIXEL+INTERVAL_V*2,titleHeight);
	lv_obj_set_pos(buttonAbout,BTN_X_PIXEL*2+INTERVAL_V*3,titleHeight);
	lv_obj_set_pos(buttonContinue,BTN_X_PIXEL*3+INTERVAL_V*4,titleHeight);
	lv_obj_set_pos(buMotorOff,INTERVAL_V,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_obj_set_pos(buttonLanguage,BTN_X_PIXEL+INTERVAL_V*2,BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	lv_obj_set_pos(buttonBack,BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);*/

	//lv_obj_set_pos(buttonWifi,INTERVAL_V,titleHeight);
	lv_obj_set_pos(buttonFan,BTN_X_PIXEL+INTERVAL_V*2,titleHeight);
	lv_obj_set_pos(buttonAbout,BTN_X_PIXEL*2+INTERVAL_V*3,titleHeight);
	//lv_obj_set_pos(buttonContinue,BTN_X_PIXEL*3+INTERVAL_V*4,titleHeight);
	//lv_obj_set_pos(buMotorOff,BTN_X_PIXEL*3+INTERVAL_V*4,titleHeight);
	lv_obj_set_pos(buttonLanguage,INTERVAL_V,titleHeight);
	lv_obj_set_pos(buttonBack,BTN_X_PIXEL*3+INTERVAL_V*4,  BTN_Y_PIXEL+INTERVAL_H+titleHeight);
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_set_pos(buttonXmode,BTN_X_PIXEL*3+INTERVAL_V*4,titleHeight);
	#endif
	lv_obj_set_pos(buttonEepromSet,INTERVAL_V,BTN_Y_PIXEL+INTERVAL_H+titleHeight);

    /*Create a label on the Image button*/
	//lv_btn_set_layout(buttonWifi, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonFan, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonAbout, LV_LAYOUT_OFF);
	//lv_btn_set_layout(buttonContinue, LV_LAYOUT_OFF);
	//lv_btn_set_layout(buMotorOff, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonLanguage, LV_LAYOUT_OFF);
	lv_btn_set_layout(buttonBack, LV_LAYOUT_OFF);
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_btn_set_layout(buttonXmode, LV_LAYOUT_OFF);
	#endif
	lv_btn_set_layout(buttonEepromSet, LV_LAYOUT_OFF);
	
    //lv_obj_t * labelWifi= lv_label_create(buttonWifi, NULL);
	lv_obj_t * labelFan = lv_label_create(buttonFan, NULL);
	lv_obj_t * label_About = lv_label_create(buttonAbout, NULL);
	//lv_obj_t * label_Continue = lv_label_create(buttonContinue, NULL);
	//lv_obj_t * label_MotorOff = lv_label_create(buMotorOff, NULL);
	lv_obj_t * label_Language = lv_label_create(buttonLanguage, NULL);
	lv_obj_t * label_Back = lv_label_create(buttonBack, NULL);
	#if ENABLED(DUAL_X_CARRIAGE)
	lv_obj_t * label_Xmode = lv_label_create(buttonXmode, NULL);
	#endif
	lv_obj_t * label_EepromSet = lv_label_create(buttonEepromSet, NULL);
	
	
	if(gCfgItems.multiple_language !=0)
	{
	       //lv_label_set_text(labelWifi, set_menu.wifi);
		//lv_obj_align(labelWifi, buttonWifi, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(labelFan, set_menu.fan);
		lv_obj_align(labelFan, buttonFan, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

		lv_label_set_text(label_About,set_menu.about);
		lv_obj_align(label_About, buttonAbout, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);

	       //lv_label_set_text(label_Continue, set_menu.breakpoint);
		//lv_obj_align(label_Continue, buttonContinue, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		//#if ENABLED(PSU_CONTROL)
		//lv_label_set_text(label_MotorOff, set_menu.shutdown);
		//#else
		//lv_label_set_text(label_MotorOff, set_menu.motoroff);
		//#endif
		//lv_obj_align(label_MotorOff, buMotorOff, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		
		lv_label_set_text(label_Language, set_menu.language);
		lv_obj_align(label_Language, buttonLanguage, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		
		lv_label_set_text(label_Back, common_menu.text_back);
		lv_obj_align(label_Back, buttonBack, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		#if ENABLED(DUAL_X_CARRIAGE)
		lv_label_set_text(label_Xmode, set_menu.Xmode);
		lv_obj_align(label_Xmode, buttonXmode, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
		#endif

		lv_label_set_text(label_EepromSet, set_menu.eepromSet);
		lv_obj_align(label_EepromSet, buttonEepromSet, LV_ALIGN_IN_BOTTOM_MID,0, BUTTON_TEXT_Y_OFFSET);
	}
}

void lv_clear_set()
{
	lv_obj_del(scr);
}

#endif
