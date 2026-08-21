/*
    CORE Echo
*/

Content.makeFrontInterface(800, 650);

Engine.loadFontAs(
    "{PROJECT_FOLDER}Fonts/Geist-VariableFont_wght.ttf",
    "Geist"
);

Engine.setGlobalFont("Geist");

const var DelayDivision = Content.getComponent("DelayDivision");
const var Delay = Content.getComponent("Delay");

const var PresetPrevious = Content.getComponent("PresetPrevious");
const var PresetName = Content.getComponent("PresetName");
const var PresetNext = Content.getComponent("PresetNext");
const var PresetRefresh = Content.getComponent("PresetRefresh");
const var PresetSave = Content.getComponent("PresetSave");

const var CoreEcho = Synth.getEffect("Hardcoded Master FX");

const var TempoSyncIndex =
    CoreEcho.getAttributeIndex("TempoSync");

const var TempoIndex =
    CoreEcho.getAttributeIndex("Tempo");

const var tempoNames = [
    "1/1",
    "1/2D",
    "1/2",
    "1/2T",
    "1/4D",
    "1/4",
    "1/4T",
    "1/8D",
    "1/8",
    "1/8T",
    "1/16D",
    "1/16",
    "1/16T",
    "1/32D",
    "1/32",
    "1/32T",
    "1/64D",
    "1/64",
    "1/64T"
];

DelayDivision.set(
    "items",
    tempoNames.join("\n")
);

DelayDivision.setValue(1);

CoreEcho.setAttribute(
    TempoIndex,
    0
);

inline function getTempoSyncState()
{
    return CoreEcho.getAttribute(TempoSyncIndex) >= 0.5;
}

inline function updateTempoUI()
{
    local synced = getTempoSyncState();

    Delay.set("enabled", !synced);
    DelayDivision.set("enabled", synced);
    DelayDivision.sendRepaintMessage();
}

const var UIWatcher = Content.addPanel(
    "UIWatcher",
    0,
    0
);

UIWatcher.set("visible", false);
UIWatcher.data.lastValue = -1;

UIWatcher.setTimerCallback(function()
{
    local value =
        CoreEcho.getAttribute(TempoSyncIndex);

    if (value != this.data.lastValue)
    {
        this.data.lastValue = value;
        updateTempoUI();
    }
});

UIWatcher.startTimer(50);

PresetPrevious.set("saveInPreset", false);
PresetName.set("saveInPreset", false);
PresetNext.set("saveInPreset", false);
PresetRefresh.set("saveInPreset", false);
PresetSave.set("saveInPreset", false);

PresetPrevious.set("text", "<");
PresetNext.set("text", ">");
PresetRefresh.set("text", "refresh");
PresetSave.set("text", "save");

const var tempoLaf =
    Content.createLocalLookAndFeel();

tempoLaf.registerFunction(
    "drawComboBox",
    function(g, obj)
    {
        local active =
            getTempoSyncState();

        g.setColour(
            0xFFF5F5F2
        );

        g.fillRoundedRectangle(
            obj.area,
            5.0
        );

        g.setColour(
            active
                ? 0xFFCFCFC8
                : 0xFFE3E3DE
        );

        g.drawRoundedRectangle(
            obj.area,
            5.0,
            1.0
        );

        g.setColour(
            active
                ? 0xFF1C1C1C
                : 0xFFA8A8A2
        );

        g.setFont(
            "Geist",
            15.0
        );

        g.drawAlignedText(
            obj.text,
            [
                10,
                0,
                obj.area[2] - 40,
                obj.area[3]
            ],
            "left"
        );

        g.setColour(
            active
                ? 0xFF6C6C6C
                : 0xFFB8B8B2
        );

        g.fillTriangle(
            [
                obj.area[2] - 16,
                obj.area[3] / 2 - 2,
                8,
                5
            ],
            Math.PI
        );
    }
);

tempoLaf.registerFunction(
    "drawPopupMenuBackground",
    function(g, obj)
    {
        g.fillAll(
            0xFFF5F5F2
        );
    }
);

tempoLaf.registerFunction(
    "drawPopupMenuItem",
    function(g, obj)
    {
        if (obj.isHighlighted)
        {
            g.setColour(
                0xFFD8D8D3
            );

            g.fillRect(
                obj.area
            );
        }

        g.setColour(
            0xFF1C1C1C
        );

        g.setFont(
            "Geist",
            13.0
        );

        g.drawAlignedText(
            obj.text,
            [
                obj.area[0] + 10,
                obj.area[1],
                obj.area[2] - 20,
                obj.area[3]
            ],
            "left"
        );
    }
);

DelayDivision.setLocalLookAndFeel(
    tempoLaf
);

const var presetLaf =
    Content.createLocalLookAndFeel();

presetLaf.registerFunction(
    "drawToggleButton",
    function(g, obj)
    {
        local area =
            obj.area;

        g.setColour(
            obj.over
                ? 0xFFE8E8E3
                : 0xFFF5F5F2
        );

        g.fillRoundedRectangle(
            area,
            5.0
        );

        g.setColour(
            0xFFCFCFC8
        );

        g.drawRoundedRectangle(
            area,
            5.0,
            1.0
        );

        g.setColour(
            0xFF1C1C1C
        );

        g.setFont(
            "Geist",
            12.0
        );

        g.drawAlignedText(
            obj.text,
            area,
            "centred"
        );
    }
);

presetLaf.registerFunction(
    "drawComboBox",
    function(g, obj)
    {
        local area =
            obj.area;

        g.setColour(
            obj.over
                ? 0xFFE8E8E3
                : 0xFFF5F5F2
        );

        g.fillRoundedRectangle(
            area,
            5.0
        );

        g.setColour(
            0xFFCFCFC8
        );

        g.drawRoundedRectangle(
            area,
            5.0,
            1.0
        );

        g.setColour(
            0xFF1C1C1C
        );

        g.setFont(
            "Geist",
            12.0
        );

        g.drawAlignedText(
            obj.text,
            [
                12,
                0,
                area[2] - 40,
                area[3]
            ],
            "left"
        );

        g.setColour(
            0xFF6C6C6C
        );

        g.fillTriangle(
            [
                area[2] - 20,
                area[3] / 2 - 2,
                8,
                5
            ],
            Math.PI
        );
    }
);

presetLaf.registerFunction(
    "drawPopupMenuBackground",
    function(g, obj)
    {
        g.fillAll(
            0xFFF5F5F2
        );
    }
);

presetLaf.registerFunction(
    "drawPopupMenuItem",
    function(g, obj)
    {
        if (obj.isHighlighted)
        {
            g.setColour(
                0xFFE8E8E3
            );

            g.fillRect(
                obj.area
            );
        }

        g.setColour(
            0xFF1C1C1C
        );

        g.setFont(
            "Geist",
            12.0
        );

        g.drawAlignedText(
            obj.text,
            [
                obj.area[0] + 12,
                obj.area[1],
                obj.area[2] - 24,
                obj.area[3]
            ],
            "left"
        );
    }
);

PresetPrevious.setLocalLookAndFeel(
    presetLaf
);

PresetName.setLocalLookAndFeel(
    presetLaf
);

PresetNext.setLocalLookAndFeel(
    presetLaf
);

PresetRefresh.setLocalLookAndFeel(
    presetLaf
);

PresetSave.setLocalLookAndFeel(
    presetLaf
);

var presetList = [];
var presetNames = [];

inline function getPresetName(path)
{
    local name = path;

    local slashIndex =
        name.lastIndexOf("/");

    local backslashIndex =
        name.lastIndexOf("\\");

    if (backslashIndex > slashIndex)
        slashIndex = backslashIndex;

    if (slashIndex != -1)
    {
        name = name.substring(
            slashIndex + 1
        );
    }

    return name.replace(
        ".preset",
        ""
    );
}

inline function refreshPresetList()
{
    local currentPreset =
        Engine.getCurrentUserPresetName();

    presetList =
        Engine.getUserPresetList();

    presetNames.clear();

    Console.print(
        "PRESET COUNT: " +
        presetList.length
    );

    for (preset in presetList)
    {
        Console.print(
            "PRESET: " +
            preset
        );

        presetNames.push(
            getPresetName(preset)
        );
    }

    PresetName.set(
        "items",
        presetNames.join("\n")
    );

    if (currentPreset != "")
    {
        local index =
            presetNames.indexOf(
                getPresetName(
                    currentPreset
                )
            );

        if (index != -1)
        {
            PresetName.setValue(
                index + 1
            );
        }
    }
}

inline function updatePresetSelector()
{
    local currentPreset =
        Engine.getCurrentUserPresetName();

    if (currentPreset == "")
        return;

    local index =
        presetNames.indexOf(
            getPresetName(
                currentPreset
            )
        );

    if (index != -1)
    {
        PresetName.setValue(
            index + 1
        );
    }
}

inline function loadPreset(index)
{
    if (
        index < 0 ||
        index >= presetList.length
    )
        return;

    Engine.loadUserPreset(
        presetList[index] +
        ".preset"
    );
}

inline function loadInitialPreset()
{
    local index =
        presetNames.indexOf(
            "default"
        );

    if (index == -1)
        return;

    loadPreset(
        index
    );

    PresetName.setValue(
        index + 1
    );
}

const var SaveOverlay =
    Content.addPanel(
        "SaveOverlay",
        0,
        0
    );

SaveOverlay.set(
    "width",
    800
);

SaveOverlay.set(
    "height",
    650
);

SaveOverlay.set(
    "visible",
    false
);

SaveOverlay.set(
    "saveInPreset",
    false
);

SaveOverlay.setPaintRoutine(
    function(g)
    {
        g.fillAll(
            0x55000000
        );
    }
);

const var SaveModal =
    Content.addPanel(
        "SaveModal",
        235,
        220
    );

SaveModal.set(
    "width",
    330
);

SaveModal.set(
    "height",
    205
);

SaveModal.set(
    "visible",
    false
);

SaveModal.set(
    "saveInPreset",
    false
);

SaveModal.setPaintRoutine(
    function(g)
    {
        local area =
            this.getLocalBounds(0);

        g.setColour(
            0xFFF5F5F2
        );

        g.fillRoundedRectangle(
            area,
            8.0
        );

        g.setColour(
            0xFFCFCFC8
        );

        g.drawRoundedRectangle(
            area,
            8.0,
            1.0
        );

        g.setColour(
            0xFF1C1C1C
        );

        g.setFont(
            "Geist",
            18.0
        );

        g.drawAlignedText(
            "save preset",
            [
                24,
                20,
                282,
                30
            ],
            "left"
        );

        g.setColour(
            0xFF6C6C6C
        );

        g.setFont(
            "Geist",
            12.0
        );

        g.drawAlignedText(
            "enter a name for your preset.",
            [
                24,
                48,
                282,
                24
            ],
            "left"
        );
    }
);

const var SavePresetName =
    Content.addLabel(
        "SavePresetName",
        259,
        300
    );

SavePresetName.set(
    "width",
    282
);

SavePresetName.set(
    "height",
    38
);

SavePresetName.set(
    "visible",
    false
);

SavePresetName.set(
    "saveInPreset",
    false
);

SavePresetName.set(
    "editable",
    true
);

SavePresetName.set(
    "text",
    ""
);

SavePresetName.set(
    "fontName",
    "Geist"
);

SavePresetName.set(
    "fontSize",
    13
);

SavePresetName.set(
    "alignment",
    "left"
);

SavePresetName.set(
    "bgColour",
    0xFFFFFFFF
);

SavePresetName.set(
    "textColour",
    0xFF1C1C1C
);

SavePresetName.set(
    "itemColour",
    0xFFCFCFC8
);

SavePresetName.set(
    "itemColour2",
    0xFF1C1C1C
);

const var SaveCancel =
    Content.addButton(
        "SaveCancel",
        361,
        359
    );

SaveCancel.set(
    "width",
    86
);

SaveCancel.set(
    "height",
    38
);

SaveCancel.set(
    "visible",
    false
);

SaveCancel.set(
    "saveInPreset",
    false
);

SaveCancel.set(
    "text",
    "cancel"
);

const var SaveConfirm =
    Content.addButton(
        "SaveConfirm",
        455,
        359
    );

SaveConfirm.set(
    "width",
    86
);

SaveConfirm.set(
    "height",
    38
);

SaveConfirm.set(
    "visible",
    false
);

SaveConfirm.set(
    "saveInPreset",
    false
);

SaveConfirm.set(
    "text",
    "save"
);

const var saveModalLaf =
    Content.createLocalLookAndFeel();

saveModalLaf.registerFunction(
    "drawToggleButton",
    function(g, obj)
    {
        local area =
            obj.area;

        g.setColour(
            obj.over
                ? 0xFFE8E8E3
                : 0xFFF5F5F2
        );

        g.fillRoundedRectangle(
            area,
            5.0
        );

        g.setColour(
            0xFFCFCFC8
        );

        g.drawRoundedRectangle(
            area,
            5.0,
            1.0
        );

        g.setColour(
            0xFF1C1C1C
        );

        g.setFont(
            "Geist",
            12.0
        );

        g.drawAlignedText(
            obj.text,
            area,
            "centred"
        );
    }
);

SaveCancel.setLocalLookAndFeel(
    saveModalLaf
);

SaveConfirm.setLocalLookAndFeel(
    saveModalLaf
);

inline function showSaveModal()
{
    SavePresetName.set(
        "text",
        ""
    );

    SaveOverlay.set(
        "visible",
        true
    );

    SaveModal.set(
        "visible",
        true
    );

    SavePresetName.set(
        "visible",
        true
    );

    SaveCancel.set(
        "visible",
        true
    );

    SaveConfirm.set(
        "visible",
        true
    );
}

inline function hideSaveModal()
{
    SaveOverlay.set(
        "visible",
        false
    );

    SaveModal.set(
        "visible",
        false
    );

    SavePresetName.set(
        "visible",
        false
    );

    SaveCancel.set(
        "visible",
        false
    );

    SaveConfirm.set(
        "visible",
        false
    );
}

const var SaveRefreshTimer =
    Content.addPanel(
        "SaveRefreshTimer",
        0,
        0
    );

SaveRefreshTimer.set(
    "visible",
    false
);

SaveRefreshTimer.set(
    "saveInPreset",
    false
);

SaveRefreshTimer.data.savedPresetName =
    "";

SaveRefreshTimer.setTimerCallback(function()
{
    this.stopTimer();

    refreshPresetList();

    local newPresetName =
        this.data.savedPresetName;

    local index =
        presetNames.indexOf(
            newPresetName
        );

    if (index != -1)
    {
        PresetName.setValue(
            index + 1
        );
    }

    updatePresetSelector();
});

inline function saveCustomPreset()
{
    local presetName =
        SavePresetName.get(
            "text"
        );

    if (presetName == "")
        return;

    SaveRefreshTimer.data.savedPresetName =
        presetName;

    Engine.saveUserPreset(
        presetName
    );

    hideSaveModal();

    SaveRefreshTimer.startTimer(
        150
    );
}

inline function onPresetName(
    component,
    value
)
{
    loadPreset(
        value - 1
    );
}

PresetName.setControlCallback(
    onPresetName
);

inline function onPresetPrevious(
    component,
    value
)
{
    if (value)
    {
        Engine.loadPreviousUserPreset(
            true
        );
    }
}

PresetPrevious.setControlCallback(
    onPresetPrevious
);

inline function onPresetNext(
    component,
    value
)
{
    if (value)
    {
        Engine.loadNextUserPreset(
            true
        );
    }
}

PresetNext.setControlCallback(
    onPresetNext
);

inline function onPresetRefresh(
    component,
    value
)
{
    if (!value)
        return;

    refreshPresetList();
    updatePresetSelector();
}

PresetRefresh.setControlCallback(
    onPresetRefresh
);

inline function onPresetSave(
    component,
    value
)
{
    if (value)
    {
        showSaveModal();
    }
}

PresetSave.setControlCallback(
    onPresetSave
);

inline function onSaveCancel(
    component,
    value
)
{
    if (value)
    {
        hideSaveModal();
    }
}

SaveCancel.setControlCallback(
    onSaveCancel
);

inline function onSaveConfirm(
    component,
    value
)
{
    if (value)
    {
        saveCustomPreset();
    }
}

SaveConfirm.setControlCallback(
    onSaveConfirm
);

const var PresetWatcher =
    Content.addPanel(
        "PresetWatcher",
        0,
        0
    );

PresetWatcher.set(
    "visible",
    false
);

PresetWatcher.data.lastPreset =
    "";

PresetWatcher.setTimerCallback(
    function()
    {
        local currentPreset =
            Engine.getCurrentUserPresetName();

        if (
            currentPreset !=
            this.data.lastPreset
        )
        {
            this.data.lastPreset =
                currentPreset;

            updatePresetSelector();
        }
    }
);

PresetWatcher.startTimer(
    100
);

updateTempoUI();
refreshPresetList();
loadInitialPreset();
hideSaveModal();